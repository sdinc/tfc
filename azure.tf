resource "azurerm_resource_group" "azure-sfefoil-com" {
  name     = "example-resources"
  location = "West Europe"
}

resource "azurerm_dns_zone" "azure-sfefoil-com" {
  name                = "azure.sfefoil.com"
  resource_group_name = azurerm_resource_group.azure-sfefoil-com
}