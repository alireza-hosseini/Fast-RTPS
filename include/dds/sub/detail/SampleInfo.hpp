#ifndef OMG_DDS_SUB_DETAIL_SAMPLE_INFO_HPP_
#define OMG_DDS_SUB_DETAIL_SAMPLE_INFO_HPP_

#include <include/fastrtps/SampleInfo.h>
#include <dds/sub/TSampleInfo.hpp>

namespace dds { 
namespace sub { 
namespace detail {

//TODO: Change namespaces --> fastdds::dds::sub::SampleInfo instead of fastrtps::SampleInfo
typedef dds::sub::TSampleInfo<eprosima::fastrtps::SampleInfo> SampleInfo;

}
}
}

#endif // OMG_DDS_SUB_DETAIL_SAMPLE_INFO_HPP_

