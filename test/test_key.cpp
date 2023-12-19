#include "test.h"

#include "encryption/Key.h"

class KeyTest : public LabTest {};

TEST_F(KeyTest, test_three_a_one) {
    const auto& standard_key = Key::get_standard_key();

    //Input for Hash: 0000011100000110000001010000010000000011000000100000000100000000
    //Output for Hash: 0010 1101 | 0010 0100 | 1010 0010 | 0101 0101 | 0000 1000 | 0100 1110 | 1000 1110 | 0010 0000
    //                                                                                                      key[0]

    //Input for Hash: 0000111100001110000011010000110000001011000010100000100100001000
    //Output for Hash: 0000 0001 | 1001 1010 | 1111 0100 | 0000 0011 | 0111 1110 | 0000 0000 | 1101 1100 | 0110 1000
    //                                                                                                      key[8]

    //Input for Hash: 0001011100010110000101010001010000010011000100100001000100010000
    //Output for Hash: 0111 0101 | 1111 0001 | 0101 0110 | 1100 1010 | 1010 1100 | 1100 1011 | 0010 1010 | 1011 0000
    //                                                                                                      key[16]

    //Input for Hash: 0001111100011110000111010001110000011011000110100001100100011000
    //Output for Hash: 1110 1000 | 0011 1111 | 1000 0111 | 0111 1100 | 0001 1010 | 1001 0101 | 0110 0000 | 1111 1000
    //                                                                                                      key[24]

    //Input for Hash: 0010011100100110001001010010010000100011001000100010000100100000
    //Output for Hash: 1001 1100 | 0100 1101 | 1111 0101 | 0010 1110 | 0101 0001 | 0010 0111 | 1011 0101 | 0000 0000
    //                                                                                                      key[32]

    //Input for Hash: 0010111100101110001011010010110000101011001010100010100100101000
    //Output for Hash: 1011 0000 | 1001 0000 | 0011 1011 | 1101 1001 | 1000 0111 | 1111 0110 | 0001 0111 | 0100 1000
    //                                                                                                      key[40]

    std::uint8_t produced_key_values[] = { 32, 142, 78, 8, 85, 162, 36, 45,
                                           104, 220, 0, 126, 3, 244, 154, 1,
                                           176, 42, 203, 172, 202, 86, 241, 117,
                                           248, 96, 149, 26, 124, 135, 63, 232,
                                           0, 181, 39, 81, 46, 245, 77, 156,
                                            72, 23, 246, 135, 217, 59, 144, 176 };

    Key::key_type expected_produced_key;
    for (int i = 0; i < 48; i++) {
        expected_produced_key[i] = produced_key_values[i];
    }

    Key::key_type produced_key = Key::produce_new_key(standard_key);

    ASSERT_EQ(produced_key, expected_produced_key);
}

TEST_F(KeyTest, test_three_b_one) {
    const auto& standard_key = Key::get_standard_key();

    const auto standard_hash = Key::hash(standard_key);
    const auto expected_standard_hash = std::uint64_t{ 11'361'817'798'440'499'784 };

    ASSERT_EQ(standard_hash, expected_standard_hash);
}

TEST_F(KeyTest, test_three_c_one) {
    auto keys = std::vector<Key::key_type>{};

    const auto minimum_hash = Key::get_smallest_hash(keys);

    const auto expected_minimum_hash = std::numeric_limits<std::uint64_t>::max();

    ASSERT_EQ(minimum_hash, expected_minimum_hash);
}

TEST_F(KeyTest, test_three_c_two) {
    auto keys = std::vector<Key::key_type>{};
    keys.reserve(1024);

    keys.emplace_back(Key::get_standard_key());
    for (auto i = std::size_t(0); i < 1023; i++) {
        keys.emplace_back(Key::produce_new_key(keys[i]));
    }

    const auto minimum_hash = Key::get_smallest_hash(keys);
    const auto expected_minimum_hash = std::uint64_t{ 30'403'176'973'399'313 };

    ASSERT_EQ(minimum_hash, expected_minimum_hash);
}

TEST_F(KeyTest, test_three_e_one) {
    auto keys = std::vector<Key::key_type>{};
    keys.reserve(1024);

    Key::key_type key_to_find;

    keys.emplace_back(Key::get_standard_key());
    for (auto i = std::size_t(0); i < 1023; i++) {
        Key::key_type next_key = Key::produce_new_key(keys[i]);
        keys.emplace_back(next_key);
        if (i == 500) {
            key_to_find = next_key;
        }
    }

    const auto hash_for_search = Key::hash(key_to_find);

    const auto found_key = Key::find_key(keys, hash_for_search);

    ASSERT_EQ(found_key, key_to_find);
}

TEST_F(KeyTest, test_three_f_two) {
    auto keys = std::vector<Key::key_type>{};
    keys.reserve(1024);

    Key::key_type key_to_find;

    keys.emplace_back(Key::get_standard_key());
    for (auto i = std::size_t(0); i < 1023; i++) {
        Key::key_type next_key = Key::produce_new_key(keys[i]);
        keys.emplace_back(next_key);
        if (i == 500) {
            key_to_find = next_key;
        }
    }

    const auto hash_for_search = Key::hash(key_to_find);

    const auto found_key = Key::find_key(keys, hash_for_search);

    ASSERT_EQ(found_key, key_to_find);
}
