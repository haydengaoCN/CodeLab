#include<iostream>

#ifndef SUNFISH_CORE_PUBLIC_REPOSITORY_SPACE_H_
#define SUNFISH_CORE_PUBLIC_REPOSITORY_SPACE_H_
typedef uint64_t RepositorySpace;
typedef uint32_t RepositorySpaceFlag;
typedef uint32_t RepositorySpaceId;
// Repository space flag.
static const RepositorySpaceFlag kRepositorySpaceFlag_Range = 0x0;
static const RepositorySpaceFlag kRepositorySpaceFlag_Id = 0x1;
static const RepositorySpaceFlag kRepositorySpaceFlag_Text = 0x2;
static const RepositorySpaceFlag kRepositorySpaceFlag_Fast_Search = 0xFFFFFFFFul;
static const uint64_t kRepositorySapceFlagMask = 0xFFFFFFFFull;

static inline RepositorySpaceFlag GetRepositorySpaceFlag(
    const RepositorySpace &space) {
  return space & kRepositorySapceFlagMask;
}

static inline RepositorySpaceId GetRepositorySpaceId(
  const RepositorySpace &space) {
  return space >> 32;
}

static inline bool IsRangeRepositorySpace(const RepositorySpace &space) {
  return (space & kRepositorySapceFlagMask) == kRepositorySpaceFlag_Range;
}

#if __cpp_constexpr >= 201304  // Support constexpr
constexpr RepositorySpace MakeRepositorySpace(
    const uint32_t id,
    const RepositorySpaceFlag flag) {
  // std::cout << static_cast<RepositorySpace>((static_cast<uint64_t>(id) << 32) | flag);
  return static_cast<RepositorySpace>((static_cast<uint64_t>(id) << 32) | flag);
}
#else
#define MakeRepositorySpace(id, flag) \
    static_cast<RepositorySpace>((static_cast<uint64_t>(id) << 32) | (flag))

#endif  // __cpp_constexpr

#endif  // SUNFISH_CORE_PUBLIC_REPOSITORY_SPACE_H_

