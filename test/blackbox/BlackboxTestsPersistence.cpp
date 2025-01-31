// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "BlackboxTests.hpp"

#if HAVE_SQLITE3

#include "RTPSAsSocketReader.hpp"
#include "RTPSAsSocketWriter.hpp"
#include "RTPSWithRegistrationReader.hpp"
#include "RTPSWithRegistrationWriter.hpp"
#include <thread>

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;

class BlackBoxPersistence : public ::testing::Test
{
public:
    const std::string& db_file_name() const
    {
        return db_file_name_;
    }
    const eprosima::fastrtps::rtps::GuidPrefix_t& guid_prefix() const
    {
        return guid_prefix_;
    }
    std::list<HelloWorld> not_received_data;

    void run_one_send_recv_test(
            RTPSWithRegistrationReader<HelloWorldType>& reader,
            RTPSWithRegistrationWriter<HelloWorldType>& writer,
            uint32_t seq_check = 0,
            bool reliable = false)
    {
        // Wait for discovery.
        writer.wait_discovery();
        reader.wait_discovery();

        std::cout << "Discovery finished." << std::endl;

        auto data = default_helloworld_data_generator();
        size_t n_samples = data.size();
        not_received_data.insert(not_received_data.end(), data.begin(), data.end());

        reader.expected_data(not_received_data);
        reader.startReception();

        // Send data
        writer.send(data);
        // In this test all data should be sent.
        ASSERT_TRUE(data.empty());

        // Block reader until reception finished or timeout.
        if (seq_check > 0)
        {
            std::cout << "Reader waiting for sequence " << seq_check << "." << std::endl;
            reader.block_until_seq_number_greater_or_equal({ 0,seq_check });
        }
        else
        {
            if (reliable)
            {
                std::cout << "Reader waiting for " << n_samples << " samples." << std::endl;
                reader.block_for_all();
            }
            else
            {
                std::cout << "Reader waiting for 2 samples." << std::endl;
                reader.block_for_at_least(2);
            }
        }

        std::cout << "Last received sequence was " << reader.get_last_received_sequence_number() << std::endl;

        std::cout << "Destroying reader..." << std::endl;
        reader.destroy();
        std::cout << "Destroying writer..." << std::endl;
        writer.destroy();

        data = reader.not_received_data();
        print_non_received_messages(data, default_helloworld_print);
        not_received_data = data;
    }

protected:
    std::string db_file_name_;
    eprosima::fastrtps::rtps::GuidPrefix_t guid_prefix_;

    virtual void SetUp()
    {
        // Get info about current test
        auto info = ::testing::UnitTest::GetInstance()->current_test_info();

        // Create DB file name from test name and PID
        std::ostringstream ss;
        ss << info->test_case_name() << "_" << info->name() << "_" << GET_PID() << ".db";
        db_file_name_ = ss.str();

        // Fill guid prefix
        int32_t* p_value = (int32_t*)guid_prefix_.value;
        *p_value++ = info->line();
        *p_value = GET_PID();
        guid_prefix_.value[8] = HAVE_SECURITY;
        guid_prefix_.value[9] = 3; //PREALLOCATED_MEMORY_MODE
        eprosima::fastrtps::rtps::LocatorList_t loc;
        eprosima::fastrtps::rtps::IPFinder::getIP4Address(&loc);
        if (loc.size() > 0)
        {
            guid_prefix_.value[10] = loc.begin()->address[14];
            guid_prefix_.value[11] = loc.begin()->address[15];
        }
        else
        {
            guid_prefix_.value[10] = 127;
            guid_prefix_.value[11] = 1;
        }
    }

    virtual void TearDown()
    {
        std::remove(db_file_name_.c_str());
    }
};

TEST_F(BlackBoxPersistence, RTPSAsNonReliableWithPersistence)
{
    RTPSWithRegistrationReader<HelloWorldType> reader(TEST_TOPIC_NAME);
    RTPSWithRegistrationWriter<HelloWorldType> writer(TEST_TOPIC_NAME);
    std::string ip("239.255.1.4");

    reader.make_persistent(db_file_name(), guid_prefix()).add_to_multicast_locator_list(ip, global_port).init();

    ASSERT_TRUE(reader.isInitialized());

    writer.make_persistent(db_file_name(), guid_prefix()).
        reliability(eprosima::fastrtps::rtps::ReliabilityKind_t::BEST_EFFORT).init();

    ASSERT_TRUE(writer.isInitialized());

    // Discover, send and receive
    run_one_send_recv_test(reader, writer, 0, false);

    // Stop and start reader and writer
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "First round finished." << std::endl;

    reader.init();
    writer.init();

    // Discover, send and receive
    run_one_send_recv_test(reader, writer, 13, false);
    reader.destroy();
    writer.destroy();

    std::cout << "Second round finished." << std::endl;
}

TEST_F(BlackBoxPersistence, AsyncRTPSAsNonReliableWithPersistence)
{
    RTPSWithRegistrationReader<HelloWorldType> reader(TEST_TOPIC_NAME);
    RTPSWithRegistrationWriter<HelloWorldType> writer(TEST_TOPIC_NAME);
    std::string ip("239.255.1.4");

    reader.make_persistent(db_file_name(), guid_prefix()).add_to_multicast_locator_list(ip, global_port).init();

    ASSERT_TRUE(reader.isInitialized());

    writer.make_persistent(db_file_name(), guid_prefix()).
        reliability(eprosima::fastrtps::rtps::ReliabilityKind_t::BEST_EFFORT).
        asynchronously(eprosima::fastrtps::rtps::RTPSWriterPublishMode::ASYNCHRONOUS_WRITER).init();

    ASSERT_TRUE(writer.isInitialized());

    // Discover, send and receive
    run_one_send_recv_test(reader, writer, 0, false);

    // Stop and start reader and writer
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "First round finished." << std::endl;

    reader.init();
    writer.init();

    // Discover, send and receive
    run_one_send_recv_test(reader, writer, 13, false);

    std::cout << "Second round finished." << std::endl;
}

TEST_F(BlackBoxPersistence, RTPSAsReliableWithPersistence)
{
    RTPSWithRegistrationReader<HelloWorldType> reader(TEST_TOPIC_NAME);
    RTPSWithRegistrationWriter<HelloWorldType> writer(TEST_TOPIC_NAME);
    std::string ip("239.255.1.4");

    reader.make_persistent(db_file_name(), guid_prefix()).add_to_multicast_locator_list(ip, global_port).
        reliability(eprosima::fastrtps::rtps::ReliabilityKind_t::RELIABLE).init();

    ASSERT_TRUE(reader.isInitialized());

    writer.make_persistent(db_file_name(), guid_prefix()).init();

    ASSERT_TRUE(writer.isInitialized());

    // Discover, send and receive
    run_one_send_recv_test(reader, writer, 0, true);

    // Stop and start reader and writer
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "First round finished." << std::endl;

    reader.init();
    writer.init();

    // Discover, send and receive
    run_one_send_recv_test(reader, writer, 20, true);

    std::cout << "Second round finished." << std::endl;
}

TEST_F(BlackBoxPersistence, AsyncRTPSAsReliableWithPersistence)
{
    RTPSWithRegistrationReader<HelloWorldType> reader(TEST_TOPIC_NAME);
    RTPSWithRegistrationWriter<HelloWorldType> writer(TEST_TOPIC_NAME);
    std::string ip("239.255.1.4");

    reader.make_persistent(db_file_name(), guid_prefix()).add_to_multicast_locator_list(ip, global_port).
        reliability(eprosima::fastrtps::rtps::ReliabilityKind_t::RELIABLE).init();

    ASSERT_TRUE(reader.isInitialized());

    writer.make_persistent(db_file_name(), guid_prefix()).history_depth(10).
        asynchronously(eprosima::fastrtps::rtps::RTPSWriterPublishMode::ASYNCHRONOUS_WRITER).init();

    ASSERT_TRUE(writer.isInitialized());

    // Discover, send and receive
    run_one_send_recv_test(reader, writer, 0, true);

    // Stop and start reader and writer
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "First round finished." << std::endl;

    reader.init();
    writer.init();

    // Discover, send and receive
    run_one_send_recv_test(reader, writer, 20, true);
    reader.destroy();
    writer.destroy();

    std::cout << "Second round finished." << std::endl;
}

#endif
