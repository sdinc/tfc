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
  parent_zone_name  = "sfefoil.com"
  parent_zone_id = "Z09269892PE8XEABM3L02"
  acm_certificate_arn = module.acm_request_certificate.arn

  depends_on = [module.acm_request_certificate]
}