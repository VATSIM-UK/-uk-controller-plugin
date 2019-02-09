#pragma once
#include "api/ApiResponse.h"
#include "api/ApiRequestBuilder.h"
#include "api/ApiInterface.h"

namespace UKControllerPlugin {
    namespace Curl {
        class CurlInterface;
        class CurlRequest;
    }  // namespace Curl
    namespace Windows {
        class WinApiInterface;
    }  // namespace Windows
}  // namespace UKControllerPlugin

namespace UKControllerPlugin {
    namespace Api {

        /*
            A class for making requests to the UKCP API.
        */
        class ApiHelper : public UKControllerPlugin::Api::ApiInterface
        {
            public:
                ApiHelper(
                    UKControllerPlugin::Curl::CurlInterface & curlApi,
                    const UKControllerPlugin::Api::ApiRequestBuilder requestBuilder,
                    UKControllerPlugin::Windows::WinApiInterface & winApi
                );

                UKControllerPlugin::Squawk::ApiSquawkAllocation CreateGeneralSquawkAssignment(
                    std::string callsign,
                    std::string origin,
                    std::string destination
                ) const override;
                UKControllerPlugin::Squawk::ApiSquawkAllocation CreateLocalSquawkAssignment(
                    std::string callsign,
                    std::string unit,
                    std::string flightRules
                ) const override;
                bool CheckApiAuthorisation(void) const override;
                void DeleteSquawkAssignment(std::string callsign) const override;
                UKControllerPlugin::Api::RemoteFileManifest FetchDependencyManifest(void) const override;
                std::string FetchRemoteFile(std::string uri) const override;
                UKControllerPlugin::Squawk::ApiSquawkAllocation GetAssignedSquawk(std::string callsign) const override;
                std::string GetApiDomain(void) const override;
                std::string GetApiKey(void) const override;
                int UpdateCheck(std::string version) const override;

                // The HTTP status codes that may be returned by the API
                static const uint64_t STATUS_OK = 200L;
                static const uint64_t STATUS_CREATED = 201L;
                static const uint64_t STATUS_NO_CONTENT = 204L;
                static const uint64_t STATUS_BAD_REQUEST = 400L;
                static const uint64_t STATUS_UNAUTHORISED = 401L;
                static const uint64_t STATUS_FORBIDDEN = 403L;
                static const uint64_t STATUS_NOT_FOUND = 404L;
                static const uint64_t STATUS_TEAPOT = 418L;
                static const uint64_t STATUS_SERVER_ERROR = 500L;
                static const uint64_t STATUS_SERVICE_UNAVAILBLE = 503L;

            private:

                ApiResponse MakeApiRequest(
                    const UKControllerPlugin::Curl::CurlRequest request
                ) const;

                UKControllerPlugin::Squawk::ApiSquawkAllocation ProcessSquawkResponse(
                    const ApiResponse response,
                    std::string callsign
                ) const;

                // For doing things on the filesystem, if we really need to
                UKControllerPlugin::Windows::WinApiInterface & winApi;

                // The API request builder, that builds our CurlRequests
                const UKControllerPlugin::Api::ApiRequestBuilder requestBuilder;

                // An interface to the Curl library.
                UKControllerPlugin::Curl::CurlInterface & curlApi;
        };
    }  // namespace Api
}  // namespace UKControllerPlugin
