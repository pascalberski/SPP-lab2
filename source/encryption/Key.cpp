#include "encryption/Key.h"
#include <util/Hash.h>

Key::key_type Key::get_standard_key() noexcept {
	auto key = key_type{};
	for (auto i = key_type::value_type(0); i < key.size(); i++) {
		key[i] = i;
	}

	return key;
}

Key::key_type Key::produce_new_key(const key_type& original_key) {
    Key::key_type new_key{};
    for (int i = 0; i < original_key.size(); i += 8) {
        std::uint64_t u64;
        std::memcpy(&u64, &original_key[i], 8);
        std::uint64_t newU64 = Hash::hash(u64);
        std::memcpy(&new_key[i], &newU64, sizeof newU64);
    }
    return new_key;
}

std::uint64_t Key::hash(const key_type& key) {
    std::uint64_t combined_hash = 0;

    for (std::size_t i = 0; i < key.size(); i += 8) {
        std::uint64_t segment = 0;
        for (std::size_t j = 0; j < 8; ++j) {
            segment |= static_cast<std::uint64_t>(key[i + j]) << (8 * j);
        }

        combined_hash ^= Hash::hash(segment);
    }

    return combined_hash;
}

std::uint64_t Key::get_smallest_hash(std::span<const key_type> keys) {
    std::uint64_t min_hash = std::numeric_limits<std::uint64_t>::max();

    if (keys.empty()) {
        return min_hash;
    }

    for (const auto& key : keys) {
        std::uint64_t hash = Key::hash(key);
        if (hash < min_hash) {
            min_hash = hash;
        }
    }

    return min_hash;
}

std::uint64_t Key::get_smallest_hash_parallel(std::span<const key_type> keys, int num_threads) {
    std::uint64_t global_min_hash = 0xFFFFFFFFFFFFFFFF;

    if (keys.empty()) {
        return global_min_hash;
    }

#pragma omp parallel for num_threads(num_threads) reduction(min:global_min_hash)
    for (std::size_t i = 0; i < keys.size(); ++i) {
        std::uint64_t hash = Key::hash(keys[i]);
        if (hash < global_min_hash) {
            global_min_hash = hash;
        }
    }

    return global_min_hash;
}

Key::key_type Key::find_key(std::span<const key_type> keys, std::uint64_t target_hash) {
    for (const auto& key : keys) {
        if (Key::hash(key) == target_hash) {
            return key;
        }
    }

    return key_type{};
}

Key::key_type Key::find_key_parallel(std::span<const key_type> keys, std::uint64_t target_hash, int num_threads) {
    key_type found_key;
    bool key_found = false;

#pragma omp parallel for num_threads(num_threads)
    for (std::size_t i = 0; i < keys.size(); ++i) {
        if (key_found) break;

        if (Key::hash(keys[i]) == target_hash) {
#pragma omp critical
            {
                if (!key_found) {
                    found_key = keys[i];
                    key_found = true;
                }
            }
        }
    }

    return found_key;
}
