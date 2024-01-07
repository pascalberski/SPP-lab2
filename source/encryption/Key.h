#pragma once

#include <array>
#include <cstdint>
#include <limits>
#include <span>

class Key {
public:
	using key_type = std::array<std::uint8_t, 48>;

	[[nodiscard]] static key_type get_standard_key() noexcept;

	static key_type produce_new_key(const key_type& original_key);

	static std::uint64_t hash(const key_type& key);

	static std::uint64_t get_smallest_hash(std::span<const key_type> keys);

	static std::uint64_t get_smallest_hash_parallel(std::span<const key_type> keys, int num_threads = 1);

	static key_type find_key(std::span<const key_type> keys, std::uint64_t target_hash);

	static key_type find_key_parallel(std::span<const key_type> keys, std::uint64_t target_hash, int num_threads = 1);

private:

};
