# Azure Notes

Using the document to track my work understanding the setup of azure and terraform. 

First I send az login which seems to work fine, it gives me a code and a link that I load in the browser. This works fine but the subscription that I get seems to be inactive. 


```bash
task: [az-sp] docker run -i -t -v ${HOME}/.ssh:/root/.ssh -v ${HOME}/.azure:/root/.azure  -v $(pwd):$(pwd) -w $(pwd) mcr.microsoft.com/azure-cli:latest az account show
{
  "environmentName": "AzureCloud",
  "homeTenantId": "*-*-*-*-*",
  "id": "*-*-*-*-*",
  "isDefault": true,
  "managedByTenants": [],
  "name": "Azure subscription 1",
  "state": "Disabled",    <------------------------------------------------
  "tenantId": "*-*-*-*-*",
  "user": {
    "name": "brodytwo@gmail.com",
    "type": "user"
  }
}
brody@brody-Precision-5540:~/workspace/github/tfc$
...
brody@brody-Precision-5540:~/workspace/github/tfc$  task tf-apply
task: [tf-apply] docker run --entrypoint="/usr/local/bin/terraform" -i -t -v ${HOME}/.aws:/root/.aws -v ${HOME}/.azure:/root/.azure -v ${HOME}/.terraform.d:/root/.terraform.d -v $(pwd):$(pwd) -w $(pwd) sdinc:latest apply --auto-approve
...

│ Error: creating Resource Group "sdinc-uswest-group": resources.GroupsClient#CreateOrUpdate: Failure responding to request: StatusCode=409 -- Original Error: autorest/azure: Service returned an error. Status=409 Code="ReadOnlyDisabledSubscription" Message="The subscription '221f806e-8f31-4070-82f0-0652493bf5c1' is disabled and therefore marked as read only. You cannot perform any write actions on this subscription until it is re-enabled."
│ 
│   with azurerm_resource_group.azure-sfefoil-com,
│   on azure.tf line 1, in resource "azurerm_resource_group" "azure-sfefoil-com":
│    1: resource "azurerm_resource_group" "azure-sfefoil-com" {
│ 
╵
task: Failed to run task "tf-apply": exit status 1
```

So I am looking to create a service principle and client certs at https://registry.terraform.io/providers/hashicorp/azuread/latest/docs/guides/service_principal_client_certificate#generating-a-client-certificate

