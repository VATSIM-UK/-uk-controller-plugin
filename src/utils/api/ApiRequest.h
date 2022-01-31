#pragma once
#include "ApiRequestData.h"
#include "Response.h"

namespace UKControllerPluginUtils::Api {
    class ApiRequestPerformerInterface;
    class ChainableRequest;

    class ApiRequest
    {
        public:
        ApiRequest(const ApiRequestData& data, ApiRequestPerformerInterface& performer, bool async = true);
        ~ApiRequest();
        auto Then(const std::function<Response(Response)>& function) -> ApiRequest;
        auto Catch(const std::function<void(std::exception_ptr exception)>& function) -> ApiRequest;
        void Await();

        private:
        // Allows continuation
        std::shared_ptr<ChainableRequest> chain;
        
        // Run on main thread or async
        bool async;
    };
} // namespace UKControllerPluginUtils::Api
