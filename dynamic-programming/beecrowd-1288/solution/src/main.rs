use std::io::stdin;

fn knapsack(weight: [usize; 100], damage: [usize; 100], capacity: usize, n: usize) -> usize {
    let mut dp = [[0; 101]; 101];

    for (i, wt) in weight.iter().take(n).enumerate() {
        let i = i + 1;

        for w in 1..=capacity {
            dp[i][w] = if wt > &w {
                dp[i - 1][w]
            } else {
                std::cmp::max(dp[i - 1][w], dp[i - 1][w - wt] + damage[i - 1])
            }
        }
    }
    dp[n][capacity]
}

fn read_input(lines: &mut std::io::Lines<std::io::StdinLock>) -> usize {
    lines
        .next()
        .expect("Uxpected EOF")
        .expect("Failed to read line")
        .parse::<usize>()
        .expect("Input is not a number")
}

fn main() {
    let mut lines = stdin().lines();

    let tests = read_input(&mut lines);
    let mut weight = [0; 100];
    let mut damage = [0; 100];

    for _ in 0..tests {
        // Quantidade de projécteis
        let n = read_input(&mut lines);

        for i in 0..n {
            let line = lines
                .next()
                .expect("Uxpected EOF")
                .expect("Failed to read line");

            let mut parts = line.split_whitespace();

            // Dano do projéctil
            damage[i] = parts
                .next()
                .expect("Uxpected EOF")
                .parse::<usize>()
                .expect("Input is not a number");

            // Peso do projéctil
            weight[i] = parts
                .next()
                .expect("Uxpected EOF")
                .parse::<usize>()
                .expect("Input is not a number");
        }

        let capacity = read_input(&mut lines); // Capacidade do canhão
        let resistence = read_input(&mut lines); // Resistência do castelo

        let result = knapsack(weight, damage, capacity, n);

        if result >= resistence {
            println!("Missao completada com sucesso");
        } else {
            println!("Falha na missao");
        }
    }
}
