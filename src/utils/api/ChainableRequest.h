#pragma once
#include "Response.h"

namespace UKControllerPluginUtils::Api {
    class ApiRequestData;
    class ApiRequestException;
    class ApiRequestPerformerInterface;

    /**
     * Hides the details of the continuation library.
     */
    class ChainableRequest
    {
        public:
        ChainableRequest(const ApiRequestData& data, ApiRequestPerformerInterface& performer);
        void Then(const std::function<Response(Response)>& function);
        void Then(const std::function<void(Response)>& function);
        void Then(const std::function<void(void)>& function);
        void Catch(const std::function<void(const ApiRequestException&)>& function);
        void Await();

        private:
        // Continuable instance
        cti::continuable<Response> continuable;
    };
} // namespace UKControllerPluginUtils::Api
