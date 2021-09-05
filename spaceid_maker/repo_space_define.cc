#include <stdint.h>

#include <limits>  // std::numeric_limits

#include "repo_space.h"

// The repository space id should be unique.
const uint32_t kGDT_Targeting_Repositoryspace_Id = 0;
const RepositorySpace kGDT_Targeting_Repositoryspace
  = MakeRepositorySpace(kGDT_Targeting_Repositoryspace_Id,
    kRepositorySpaceFlag_Range);

const uint32_t kEXP_Keyword_Repositoryspace_Id = 1;
const RepositorySpace kEXP_Keyword_Repositoryspace
  = MakeRepositorySpace(kEXP_Keyword_Repositoryspace_Id,
    kRepositorySpaceFlag_Id);

const uint32_t kEXP_Word_Repositoryspace_Id = 2;
const RepositorySpace kEXP_Word_Repositoryspace
  = MakeRepositorySpace(kEXP_Word_Repositoryspace_Id,
  kRepositorySpaceFlag_Id);

const uint32_t kGDT_Property_Repositoryspace_Id = 3;
const RepositorySpace kGDT_Property_Repositoryspace
  = MakeRepositorySpace(kGDT_Property_Repositoryspace_Id,
  kRepositorySpaceFlag_Range);
const uint64_t kGDT_Property_Trivial_Id = 0x100000000ull;

const uint32_t kWechat_Account_Repositoryspace_Id = 4;
const RepositorySpace kWechat_Account_Repositoryspace
  = MakeRepositorySpace(kWechat_Account_Repositoryspace_Id,
  kRepositorySpaceFlag_Id);
const uint64_t kWechat_Account_Trivial_Id
  = std::numeric_limits<uint64_t>::max();

const uint32_t kWUId_Repositoryspace_Id = 5;
const RepositorySpace kWUId_Repositoryspace =
    MakeRepositorySpace(kWUId_Repositoryspace_Id, kRepositorySpaceFlag_Id);

const uint32_t kMaterial_Repositoryspace_Id = 6;
const RepositorySpace kMaterial_Repositoryspace =
    MakeRepositorySpace(kMaterial_Repositoryspace_Id, kRepositorySpaceFlag_Id);

const uint32_t kGDT_PosCrtPt_Repositoryspace_Id = 7;
const RepositorySpace kGDT_PosCrtPt_Repositoryspace =
    MakeRepositorySpace(kGDT_PosCrtPt_Repositoryspace_Id,
        kRepositorySpaceFlag_Id);

const uint32_t kWX_ADRemarketing_Repositoryspace_Id = 8;
const RepositorySpace kWX_ADRemarketing_Repositoryspace =
    MakeRepositorySpace(kWX_ADRemarketing_Repositoryspace_Id,
        kRepositorySpaceFlag_Id);

const uint32_t kKeyword_RepositorySpace_Id = 9;
const RepositorySpace kKeyword_Repositoryspace =
    MakeRepositorySpace(kKeyword_RepositorySpace_Id,
        kRepositorySpaceFlag_Text);

const uint32_t kTerm_RepositorySpace_Id = 10;
const RepositorySpace kTerm_Repositoryspace =
    MakeRepositorySpace(kTerm_RepositorySpace_Id,
        kRepositorySpaceFlag_Text);

const uint32_t kTopic_RepositorySpace_Id = 11;
const RepositorySpace kTopic_Repositoryspace =
    MakeRepositorySpace(kTopic_RepositorySpace_Id,
        kRepositorySpaceFlag_Id);

const uint32_t kCategory_RepositorySpace_Id = 12;
const RepositorySpace kCategory_Repositoryspace =
    MakeRepositorySpace(kCategory_RepositorySpace_Id,
        kRepositorySpaceFlag_Id);

const uint32_t kEmbedding_RepositorySpace_Id = 13;
const RepositorySpace kEmbedding_Repositoryspace =
    MakeRepositorySpace(kEmbedding_RepositorySpace_Id,
        kRepositorySpaceFlag_Id);

const uint32_t kFrequency_Capping_RepositorySpace_Id = 14;
const RepositorySpace kFrequency_Capping_Repositoryspace =
    MakeRepositorySpace(kFrequency_Capping_RepositorySpace_Id,
                        kRepositorySpaceFlag_Range);

const uint32_t kBusinessContent_RepositorySpace_Id = 15;
const RepositorySpace kBusinessContent_RepositorySpace =
    MakeRepositorySpace(kBusinessContent_RepositorySpace_Id,
                        kRepositorySpaceFlag_Range);

const uint32_t kContractAd_FrequencyControl_RepositorySpace_Id = 16;
const RepositorySpace kContractAd_FrequencyControl_RepositorySpace =
    MakeRepositorySpace(kContractAd_FrequencyControl_RepositorySpace_Id,
                        kRepositorySpaceFlag_Range);

const uint32_t kWeChat_Ad_Behavior_Remarketing_RepositorySpace_Id = 17;
const RepositorySpace kWeChat_Ad_Behavior_Remarketing_RepositorySpace =
    MakeRepositorySpace(kWeChat_Ad_Behavior_Remarketing_RepositorySpace_Id,
                        kRepositorySpaceFlag_Range);

const uint32_t kMulti_Siteset_Traffic_Target_RepositorySpace_Id = 18;
const RepositorySpace kMulti_Siteset_Traffic_Target_RepositorySpace =
    MakeRepositorySpace(kMulti_Siteset_Traffic_Target_RepositorySpace_Id,
                        kRepositorySpaceFlag_Range);

const uint32_t kSdk_Version_RepositorySpace_Id = 19;
const RepositorySpace kSdk_Version_RepositorySpace =
    MakeRepositorySpace(kSdk_Version_RepositorySpace_Id,
                        kRepositorySpaceFlag_Range);

const uint32_t kAms_Industry_Id_Shield_RepositorySpace_Id = 20;
const RepositorySpace kAms_Industry_Id_Shield_RepositorySpace =
    MakeRepositorySpace(kAms_Industry_Id_Shield_RepositorySpace_Id,
                        kRepositorySpaceFlag_Range);

const uint32_t kMp_TId_Class_Black_List_RepositorySpace_Id = 21;
const RepositorySpace kMp_TId_Class_Black_List_RepositorySpace =
    MakeRepositorySpace(kMp_TId_Class_Black_List_RepositorySpace_Id,
                        kRepositorySpaceFlag_Range);

const uint32_t kWechat_Version_Filter_RepositorySpace_Id = 22;
const RepositorySpace kWechat_Version_Filter_RepositorySpace =
    MakeRepositorySpace(kWechat_Version_Filter_RepositorySpace_Id,
                        kRepositorySpaceFlag_Range);

const uint32_t kExclude_Converted_Audience_By_ProductId_RepositorySpace_Id = 23;
const RepositorySpace kExclude_Converted_Audience_By_ProductId_RepositorySpace =
    MakeRepositorySpace(kExclude_Converted_Audience_By_ProductId_RepositorySpace_Id,
                        kRepositorySpaceFlag_Id);

const uint32_t kAdCreativeId_RepositorySpace_Id = 24;
const RepositorySpace kAdCreativeId_RepositorySpace =
    MakeRepositorySpace(kAdCreativeId_RepositorySpace_Id, kRepositorySpaceFlag_Id);

const uint32_t kFast_Search_RepositorySpace_Id = 0xFFFFFFFFul;
const RepositorySpace kFast_Search_Repositoryspace =
MakeRepositorySpace(kFast_Search_RepositorySpace_Id,
kRepositorySpaceFlag_Fast_Search);

int main() {
  return 0;
}
