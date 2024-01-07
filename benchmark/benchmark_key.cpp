#include "benchmark.h"

#include "encryption/Key.h"

#include <iostream>

static void benchmark_three_d_one(benchmark::State& state) {
	const auto number_threads = state.range(0);

	const auto& keys = Holder::get_keys();

	for (auto _ : state) {
		const auto val = Key::get_smallest_hash_parallel(keys, number_threads);
		benchmark::DoNotOptimize(val);
	}

	const auto serial_answer = Key::get_smallest_hash(keys);
	const auto parallel_answer = Key::get_smallest_hash_parallel(keys, number_threads);

	if (serial_answer != parallel_answer) {
		std::cerr << "Serial and parallel answers don't match!\n";
	}
}

static void benchmark_three_f_one(benchmark::State& state) {
	const auto number_threads = state.range(0);

	for (auto _ : state) {
	}
}

BENCHMARK(benchmark_three_d_one)->Unit(benchmark::kMillisecond)->Arg(1);
BENCHMARK(benchmark_three_d_one)->Unit(benchmark::kMillisecond)->Arg(2);
BENCHMARK(benchmark_three_d_one)->Unit(benchmark::kMillisecond)->Arg(4);
BENCHMARK(benchmark_three_d_one)->Unit(benchmark::kMillisecond)->Arg(8);
BENCHMARK(benchmark_three_d_one)->Unit(benchmark::kMillisecond)->Arg(16);
BENCHMARK(benchmark_three_d_one)->Unit(benchmark::kMillisecond)->Arg(32);
BENCHMARK(benchmark_three_d_one)->Unit(benchmark::kMillisecond)->Arg(64);
BENCHMARK(benchmark_three_d_one)->Unit(benchmark::kMillisecond)->Arg(96);

BENCHMARK(benchmark_three_f_one)->Unit(benchmark::kMillisecond)->Arg(1);
BENCHMARK(benchmark_three_f_one)->Unit(benchmark::kMillisecond)->Arg(2);
BENCHMARK(benchmark_three_f_one)->Unit(benchmark::kMillisecond)->Arg(4);
