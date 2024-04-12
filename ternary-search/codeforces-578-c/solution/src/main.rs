use std::io;

const EPS: f64 = 5e-7;

fn weakness(x: f64, values: &Vec<f64>) -> f64 {
    let first = values[0] - x;
    let mut running_sum_pos = first;
    let mut running_sum_neg = first;
    let mut max = f64::abs(first);

    for value in values.iter().skip(1) {
        let value = value - x;
        running_sum_neg = value.min(value + running_sum_neg);
        running_sum_pos = value.max(value + running_sum_pos);

        max = max.max(running_sum_pos.max(-running_sum_neg));
    }
    max
}

fn main() {
    let mut lines = io::stdin().lines();
    let _ = lines
        .next()
        .expect("Unexpected EOF")
        .expect("Failed to read line");

    let values: Vec<_> = lines
        .next()
        .expect("Unexpected EOF")
        .expect("Failed to read line")
        .split_whitespace()
        .map(|x| x.parse::<f64>().expect("Input not formatted correctly"))
        .collect();

    let (mut lb, mut ub) = values.iter().fold((f64::MAX, f64::MIN), |(min, max), x| {
        (f64::min(min, *x), f64::max(max, *x))
    });

    let x = loop {
        let m1 = lb + (ub - lb) / 3.;
        let m2 = ub - (ub - lb) / 3.;

        let w1 = weakness(m1, &values);
        let w2 = weakness(m2, &values);

        if w2 > w1 {
            ub = m2;
        } else {
            lb = m1;
        }
        let error = f64::abs(w2 - w1);
        if error < EPS {
            break (m1 + m2) / 2.;
        }
    };
    let res = weakness(x, &values);
    println!("{res:.6}");
}
