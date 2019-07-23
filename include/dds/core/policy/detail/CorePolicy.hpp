#ifndef OMG_DDS_QOS_DETAIL_CORE_POLICY_HPP_
#define OMG_DDS_QOS_DETAIL_CORE_POLICY_HPP_

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

//TODO: Fix this file when Policies are implemented
//For now, we use fastrtps Policies. Change typedef when new dds policies are created
//#include <fastdds/dds/core/policy/CorePolicy.hpp>
#include <fastrtps/qos/QosPolicies.h>

#include <dds/core/policy/TCorePolicy.hpp>

namespace dds {
namespace core {
namespace policy {
namespace detail {

#ifdef OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT

typedef dds::core::policy::TDataRepresentation<eprosima::fastrtps::DataRepresentationQosPolicy>
DataRepresentation;

#endif // OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT

typedef dds::core::policy::TDeadline<eprosima::fastrtps::DeadlineQosPolicy>
Deadline;

typedef dds::core::policy::TDestinationOrder<eprosima::fastrtps::DestinationOrderQosPolicy>
DestinationOrder;

typedef dds::core::policy::TDurability<eprosima::fastrtps::DurabilityQosPolicy>
Durability;

#ifdef OMG_DDS_PERSISTENCE_SUPPORT

typedef dds::core::policy::TDurabilityService<eprosima::fastrtps::DurabilityServiceQosPolicy>
DurabilityService;

#endif // OMG_DDS_PERSISTENCE_SUPPORT

//typedef dds::core::policy::TEntityFactory<eprosima::fastrtps::EntityFactory>
//EntityFactory;

typedef dds::core::policy::TGroupData<eprosima::fastrtps::GroupDataQosPolicy>
GroupData;

typedef dds::core::policy::THistory<eprosima::fastrtps::HistoryQosPolicy>
History;

typedef dds::core::policy::TLatencyBudget<eprosima::fastrtps::LatencyBudgetQosPolicy>
LatencyBudget;

typedef dds::core::policy::TLifespan<eprosima::fastrtps::LifespanQosPolicy>
Lifespan;

typedef dds::core::policy::TLiveliness<eprosima::fastrtps::LivelinessQosPolicy>
Liveliness;

typedef dds::core::policy::TOwnership<eprosima::fastrtps::OwnershipQosPolicy>
Ownership;

#ifdef OMG_DDS_OWNERSHIP_SUPPORT

typedef dds::core::policy::TOwnershipStrength<eprosima::fastrtps::OwnershipStrengthQosPolicy>
OwnershipStrength;

#endif //OMG_DDS_OWNERSHIP_SUPPORT

typedef dds::core::policy::TPartition<eprosima::fastrtps::PartitionQosPolicy>
Partition;

typedef dds::core::policy::TPresentation<eprosima::fastrtps::PresentationQosPolicy>
Presentation;
        
//typedef dds::core::policy::TReaderDataLifecycle<eprosima::fastrtps::ReaderDataLifecycle>
//ReaderDataLifecycle;

typedef dds::core::policy::TReliability<eprosima::fastrtps::ReliabilityQosPolicy>
Reliability;

typedef dds::core::policy::TResourceLimits<eprosima::fastrtps::ResourceLimitsQosPolicy>
ResourceLimits;

typedef dds::core::policy::TTimeBasedFilter<eprosima::fastrtps::TimeBasedFilterQosPolicy>
TimeBasedFilter;

typedef dds::core::policy::TTopicData<eprosima::fastrtps::TopicDataQosPolicy>
TopicData;

typedef dds::core::policy::TTransportPriority<eprosima::fastrtps::TransportPriorityQosPolicy>
TransportPriority;

#ifdef OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT

typedef dds::core::policy::TTypeConsistencyEnforcement<eprosima::fastrtps::TypeConsistencyEnforcementQosPolicy>
TypeConsistencyEnforcement;

#endif // OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT

typedef dds::core::policy::TUserData<eprosima::fastrtps::UserDataQosPolicy>
UserData;

//typedef dds::core::policy::TWriterDataLifecycle<eprosima::fastrtps::WriterDataLifecycle>
//WriterDataLifecycle;

}
}
}
}

#endif // OMG_DDS_QOS_DETAIL_CORE_POLICY_HPP_
