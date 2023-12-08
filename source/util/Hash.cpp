#include "util/Hash.h"

Hash::hash_type Hash::hash(const std::uint64_t input) noexcept {
	const std::uint64_t A = 5647095006226412969ULL;
	const std::uint64_t B = 41413938183913153ULL;
	const std::uint64_t C = 6225658194131981369ULL;

	std::uint64_t result = ((((input >> 14) + A) + ((input << 54) ^ B)) << 4) ^ ((input % C) * 137);
	return result;
}

Hash::hash_type Hash::hash(const std::uint32_t value) noexcept {
	const auto promoted = static_cast<std::uint64_t>(value);
	return hash(promoted);
}

Hash::hash_type Hash::hash(const std::uint16_t value) noexcept {
	const auto promoted = static_cast<std::uint64_t>(value);
	return hash(promoted);
}

Hash::hash_type Hash::hash(const std::uint8_t value) noexcept {
	const auto promoted = static_cast<std::uint64_t>(value);
	return hash(promoted);
}

Hash::hash_type Hash::combine_hashes(const hash_type first_hash, const hash_type second_hash) noexcept {
	return first_hash ^ second_hash;
}
