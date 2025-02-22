// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include <azure/identity/workload_identity_credential.hpp>
#include <azure/service/client.hpp>

#include <iostream>

// The following environment variables must be set before running the sample.
// * AZURE_TENANT_ID: Tenant ID for the Azure account.
// * AZURE_CLIENT_ID: The Client ID to authenticate the request.
// * AZURE_CLIENT_CERTIFICATE_PATH: The path to a client certificate.
std::string GetTenantId() { return std::getenv("AZURE_TENANT_ID"); }
std::string GetClientId() { return std::getenv("AZURE_CLIENT_ID"); }
std::string GetTokenFilePath() { return std::getenv("AZURE_FEDERATED_TOKEN_FILE"); }

int main()
{
  try
  {
    // Step 1: Initialize Workload Identity Credential.
    auto workloadIdentityCredential = std::make_shared<Azure::Identity::WorkloadIdentityCredential>(
        GetTenantId(), GetClientId(), GetTokenFilePath());

    // Step 2: Pass the credential to an Azure Service Client.
    Azure::Service::Client azureServiceClient("serviceUrl", workloadIdentityCredential);

    // Step 3: Start using the Azure Service Client.
    azureServiceClient.DoSomething(Azure::Core::Context::ApplicationContext);

    std::cout << "Success!" << std::endl;
  }
  catch (const Azure::Core::Credentials::AuthenticationException& exception)
  {
    // Step 4: Handle authentication errors, if needed
    // (invalid credential parameters, insufficient permissions).
    std::cout << "Authentication error: " << exception.what() << std::endl;
    return 1;
  }

  return 0;
}
