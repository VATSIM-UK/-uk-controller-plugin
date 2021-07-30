#include "pch/pch.h"
#include "message/UserMessager.h"
#include "mock/MockEuroscopePluginLoopbackInterface.h"
#include "message/MessageSerializableInterface.h"

using UKControllerPluginTest::Euroscope::MockEuroscopePluginLoopbackInterface;
using UKControllerPlugin::Message::UserMessager;
using UKControllerPlugin::Message::MessageSerializableInterface;
using ::testing::NiceMock;

namespace UKControllerPluginTest {
    namespace Message {

        class TestUserMessage : public UKControllerPlugin::Message::MessageSerializableInterface
        {
            // Inherited via MessageSerializableInterface
            std::string MessageHandler(void) const override
            {
                return "Test Handler";
            }

            std::string MessageSender(void) const override
            {
                return "Test Sender";
            }

            std::string MessageString(void) const override
            {
                return "Test Message";
            }

            bool MessageShowHandler(void) const override
            {
                return true;
            }

            bool MessageMarkUnread(void) const override
            {
                return false;
            }

            bool MessageOverrideBusy(void) const override
            {
                return true;
            }

            bool MessageFlashHandler(void) const override
            {
                return false;
            }

            bool MessageRequiresConfirm(void) const override
            {
                return true;
            }
        };

        TEST(UserMessager, TestItCanSendAMessage)
        {
            NiceMock<MockEuroscopePluginLoopbackInterface> mockPlugin;

            EXPECT_CALL(
                    mockPlugin,
                    ChatAreaMessage("Test Handler", "Test Sender", "Test Message", true, false, true, false, true)
                )
                .Times(1);

            UserMessager messager(mockPlugin);
            TestUserMessage testMessage;

            messager.SendMessageToUser(testMessage);
        }
    }  // namespace Message
}  // namespace UKControllerPluginTest
