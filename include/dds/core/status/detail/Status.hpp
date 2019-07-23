#ifndef OMG_DDS_CORE_STATUS_DETAIL_STATUS_HPP_
#define OMG_DDS_CORE_STATUS_DETAIL_STATUS_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Corp.
 * Copyright 2010, Real-Time Innovations, Inc.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <dds/core/status/TStatus.hpp>

//TODO: Fix this file when all Statuses are implemented
//#include <fastdds/dds/core/status/Status.hpp>

#include <fastrtps/qos/LivelinessChangedStatus.h>
#include <fastrtps/qos/LivelinessLostStatus.h>
#include <fastrtps/qos/DeadlineMissedStatus.h>
#include <fastrtps/qos/ParameterList.h>
#include <fastrtps/qos/ParameterTypes.h>
#include <fastrtps/qos/QosPolicies.h>
#include <fastrtps/qos/ReaderQos.h>
#include <fastrtps/qos/WriterQos.h>
#include <fastrtps/qos/SampleRejectedStatus.hpp>
#include <fastrtps/qos/IncompatibleQosStatus.hpp>
#include <fastrtps/qos/SampleLostStatus.hpp>

namespace dds {
namespace core {
namespace status {
namespace detail {

//typedef dds::core::status::TInconsistentTopicStatus<eprosima::fastrtps::InconsistentTopicStatus>
//InconsistentTopicStatus;

typedef dds::core::status::TLivelinessChangedStatus<eprosima::fastrtps::LivelinessChangedStatus>
LivelinessChangedStatus;

typedef dds::core::status::TLivelinessLostStatus<eprosima::fastrtps::LivelinessLostStatus>
LivelinessLostStatus;

typedef dds::core::status::TOfferedDeadlineMissedStatus<eprosima::fastrtps::OfferedDeadlineMissedStatus>
OfferedDeadlineMissedStatus;

typedef dds::core::status::TOfferedIncompatibleQosStatus<eprosima::fastrtps::OfferedIncompatibleQosStatus>
OfferedIncompatibleQosStatus;

//typedef dds::core::status::TPublicationMatchedStatus<eprosima::fastrtps::PublicationMatchedStatus>
//PublicationMatchedStatus;

typedef dds::core::status::TSampleRejectedStatus<eprosima::fastrtps::SampleRejectedStatus>
SampleRejectedStatus;

typedef dds::core::status::TRequestedDeadlineMissedStatus<eprosima::fastrtps::RequestedDeadlineMissedStatus>
RequestedDeadlineMissedStatus;

typedef dds::core::status::TRequestedIncompatibleQosStatus<eprosima::fastrtps::RequestedIncompatibleQosStatus>
RequestedIncompatibleQosStatus;

typedef dds::core::status::TSampleLostStatus<eprosima::fastrtps::SampleLostStatus>
SampleLostStatus;

//typedef dds::core::status::TSubscriptionMatchedStatus<eprosima::fastrtps::SubscriptionMatchedStatus>
//SubscriptionMatchedStatus;

}
}
}
}

#endif // OMG_DDS_CORE_STATUS_DETAIL_STATUS_HPP_
