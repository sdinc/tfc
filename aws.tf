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
  aliases           = ["www.sfefoil.com", "sfefoil.com"]
  dns_alias_enabled = true
  parent_zone_id = "Z09269892PE8XEABM3L02"
  acm_certificate_arn = module.acm_request_certificate.arn

  depends_on = [module.acm_request_certificate]
}

module "cdn_sd" {
  #checkov:skip=CKV_TF_1:Not sure about this one
  source = "cloudposse/cloudfront-s3-cdn/aws"
  version = "0.92.0"

  origin_bucket = "specialtydiagnostics"
  namespace         = "specialtydiagnostics"
  stage             = "prod"
  name              = "web"
  aliases           = ["sd.sfefoil.com"]
  dns_alias_enabled = true
  parent_zone_id = "Z09269892PE8XEABM3L02"
  acm_certificate_arn = module.acm_request_certificate.arn

  depends_on = [module.acm_request_certificate, aws_s3_bucket.sd]
}

resource "aws_s3_bucket" "sd" {
  #checkov:skip=CKV2_AWS_6:we want it to be public read access
  #checkov:skip=CKV_AWS_18:do not need loging, saving costs
  #checkov:skip=CKV_AWS_21: do not need versioning, saving costs
  #checkov:skip=CKV_AWS_56:we want it to be public read access
  #checkov:skip=CKV2_AWS_61:no need as the content is backed up in git
  #checkov:skip=CKV2_AWS_62:no need for events this is just a static website
  #checkov:skip=CKV_AWS_144:no need for s3 replication as this is just a static website
  #checkov:skip=CKV_AWS_145:no need for kms encryption
  bucket = "specialtydiagnostics"

  tags = {
    Name        = "specialtydiagnostics"
    Environment = "prod"
  }

}
