/* Creates an example of the knapsack problem where the greedy algorithm does not work. */
use rand::Rng;
use std::cmp::Ordering;

fn knapsack_greedy(items: &mut Vec<(usize, usize)>, capacity: usize) -> usize {
    items.sort_by(|a, b| {
        let a_ratio = a.1 as f64 / a.0 as f64;
        let b_ratio = b.1 as f64 / b.0 as f64;
        b_ratio.partial_cmp(&a_ratio).unwrap_or(Ordering::Equal)
    });

    let mut total_weight = 0;
    let mut total_value = 0;

    for (weight, value) in items.iter() {
        if total_weight + weight <= capacity {
            total_weight += weight;
            total_value += value;
        }
    }

    total_value
}

fn knapsack_dynamic(items: &[(usize, usize)], capacity: usize) -> usize {
    let mut dp = vec![vec![0; capacity + 1]; items.len() + 1];

    for (i, (weight, value)) in items.iter().enumerate() {
        let i = i + 1;
        for w in 1..=capacity {
            dp[i][w] = if *weight <= w {
                dp[i - 1][w].max(dp[i - 1][w - weight] + value)
            } else {
                dp[i - 1][w]
            }
        }
    }
    dp[items.len()][capacity]
}
fn main() {
    let mut rng = rand::thread_rng();
    let mut items = vec![(0, 0); 5];
    let mut count = 0;
    let capacity = 100;

    loop {
        for item in items.iter_mut() {
            loop {
                item.0 = rng.gen_range(1..100); // Weight
                item.1 = rng.gen_range(100..1000); // Value

                if (item.0 as f64) < (capacity as f64) / 3.
                    && (item.1 as f64 / item.0 as f64) < 15.
                    && (item.1 as f64 / item.0 as f64) > 10.
                {
                    break;
                }
            }
        }

        let greedy = knapsack_greedy(&mut items, capacity);
        let dynamic = knapsack_dynamic(&items, capacity);
        if greedy != dynamic {
            println!("Greedy: {}, Dynamic: {}", greedy, dynamic);
            println!("{:?}", items);
            break;
        }
        count += 1;
        if count % 1000000 == 0 {
            println!("Greedy: {}, Dynamic: {}", greedy, dynamic);
        }
    }
}
