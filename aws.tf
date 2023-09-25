# create acm and explicitly set it to us-east-1 provider
module "acm_request_certificate" {
  #checkov:skip=CKV_TF_1:Not sure about this one
  source = "cloudposse/acm-request-certificate/aws"
  version = "0.16.3"

  domain_name                       = "sfefoil.com"
  subject_alternative_names         = ["*.sfefoil.com"]
  process_domain_validation_options = true
  ttl                               = "300"
}

module "cdn" {
  #checkov:skip=CKV_TF_1:Not sure about this one
  source = "cloudposse/cloudfront-s3-cdn/aws"
  version = "0.92.0"

  origin_bucket = "sfefoil"
  namespace         = "sfefoil"
  stage             = "prod"
  name              = "web"
  aliases           = ["www.sfefoil.com"]
  dns_alias_enabled = true
  parent_zone_id = "Z09269892PE8XEABM3L02"
  acm_certificate_arn = module.acm_request_certificate.arn

  depends_on = [module.acm_request_certificate]
}

resource "aws_s3_bucket" "sd" {
  #checkov:skip=CKV2_AWS_6:we want it to be public read access
  #checkov:skip=CKV_AWS_18:do not need loging, saving costs
  #checkov:skip=CKV_AWS_20:we want it to be public read access
  #checkov:skip=CKV_AWS_21: do not need versioning, saving costs
  #checkov:skip=CKV_AWS_53:we want it to be public read access
  #checkov:skip=CKV_AWS_54:we want it to be public read access
  #checkov:skip=CKV_AWS_55:we want it to be public read access
  #checkov:skip=CKV_AWS_56:we want it to be public read access
  #checkov:skip=CKV2_AWS_61:no need as the content is backed up in git
  #checkov:skip=CKV2_AWS_62:no need for events this is just a static website
  #checkov:skip=CKV_AWS_144:no need for s3 replication as this is just a static website with TODO:cloud front
  #checkov:skip=CKV_AWS_145:no need for kms encryption

  bucket = "specialtydiagnostics"

  tags = {
    Name        = "specialtydiagnostics"
    Environment = "prod"
  }

}

resource "aws_s3_bucket_website_configuration" "sd" {
  #checkov:skip=CKV_AWS_54:we want it to be public read access
  bucket = aws_s3_bucket.sd.id

  index_document {
    suffix = "index.html"
  }
}


resource "aws_s3_bucket_ownership_controls" "sd" {
  bucket = aws_s3_bucket.sd.id
  rule {
    object_ownership = "BucketOwnerPreferred"
  }
}

resource "aws_s3_bucket_public_access_block" "sd" {
  #checkov:skip=CKV_AWS_53:we want it to be public read access
  #checkov:skip=CKV_AWS_54:we want it to be public read access
  #checkov:skip=CKV_AWS_55:we want it to be public read access
  #checkov:skip=CKV_AWS_56:we want it to be public read access
  bucket = aws_s3_bucket.sd.id

  block_public_acls       = false
  block_public_policy     = false
  ignore_public_acls      = false
  restrict_public_buckets = false
}

resource "aws_s3_bucket_acl" "example" {
  depends_on = [
    aws_s3_bucket_ownership_controls.sd,
    aws_s3_bucket_public_access_block.sd,
  ]

  bucket = aws_s3_bucket.sd.id
  acl    = "public-read"
}