#include "airfield/AirfieldModel.h"
#include "airfield/AirfieldCollection.h"
#include "controller/ActiveCallsign.h"
#include "controller/ControllerPosition.h"

using UKControllerPlugin::Airfield::AirfieldCollection;
using UKControllerPlugin::Airfield::AirfieldModel;
using UKControllerPlugin::Controller::ActiveCallsign;
using UKControllerPlugin::Controller::ControllerPosition;

namespace UKControllerPluginTest {
    namespace AirfieldOwnership {

        TEST(AirfieldCollection, AddAirfieldThrowsExceptionIfAlreadyAdded)
        {
            AirfieldCollection collection;
            collection.AddAirfield(std::unique_ptr<AirfieldModel>(new AirfieldModel("EGKK", {})));
            EXPECT_THROW(
                collection.AddAirfield(std::unique_ptr<AirfieldModel>(new AirfieldModel("EGKK", {"EGKK_DEL"}))),
                std::invalid_argument);
        }

        TEST(AirfieldCollection, FetchAirfieldByIcaoThrowsExceptionIfNotUkAirfield)
        {
            AirfieldCollection collection;
            EXPECT_THROW(static_cast<void>(collection.FetchAirfieldByIcao("LFPG")), std::out_of_range);
        }

        TEST(AirfieldCollection, FetchAirfieldByIcaoThrowsExceptionIfNoAirfields)
        {
            AirfieldCollection collection;
            EXPECT_THROW(static_cast<void>(collection.FetchAirfieldByIcao("EGLL")), std::out_of_range);
        }

        TEST(AirfieldCollection, FetchAirfieldByIcaoThrowsExceptionIfNotFound)
        {
            AirfieldCollection collection;
            collection.AddAirfield(std::unique_ptr<AirfieldModel>(new AirfieldModel("EGKK", {})));
            EXPECT_THROW(static_cast<void>(collection.FetchAirfieldByIcao("EGLL")), std::out_of_range);
        }

        TEST(AirfieldCollection, FetchAirfieldByIcaoReturnsAirfieldIfFound)
        {
            AirfieldCollection collection;
            std::unique_ptr<AirfieldModel> airfield(new AirfieldModel("EGKK", {}));
            AirfieldModel* airfieldRaw = airfield.get();

            collection.AddAirfield(std::move(airfield));
            EXPECT_TRUE(*airfieldRaw == collection.FetchAirfieldByIcao("EGKK"));
        }

        TEST(AirfieldCollection, GetSizeReturnsNumberOfItemsInCollection)
        {
            AirfieldCollection collection;
            EXPECT_EQ(0, collection.GetSize());
            collection.AddAirfield(std::unique_ptr<AirfieldModel>(new AirfieldModel("EGKK", {})));
            collection.AddAirfield(std::unique_ptr<AirfieldModel>(new AirfieldModel("EGLL", {})));
            EXPECT_EQ(2, collection.GetSize());
        }

        TEST(AirfieldCollection, ItIteratesTheCollection)
        {
            AirfieldCollection collection;
            collection.AddAirfield(std::unique_ptr<AirfieldModel>(new AirfieldModel("EGKK", {})));
            collection.AddAirfield(std::unique_ptr<AirfieldModel>(new AirfieldModel("EGLL", {})));

            std::vector<std::string> airfields;
            collection.ForEach(
                [&airfields](const AirfieldModel& airfield) { airfields.push_back(airfield.GetIcao()); });

            std::vector<std::string> expected({"EGKK", "EGLL"});
            EXPECT_EQ(expected, airfields);
        }
    } // namespace AirfieldOwnership
} // namespace UKControllerPluginTest
