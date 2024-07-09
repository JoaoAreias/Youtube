#![allow(dead_code)]
struct Solution;

impl Solution {
    pub fn max_profit(k: i32, prices: Vec<i32>) -> i32 {
        let k = k as usize;

        if k >= prices.len() / 2 {
            let mut total = 0;
            for w in prices.windows(2) {
                total += 0.max(w[1] - w[0]);
            }
            return total;
        }

        let mut current = [[0; 2]; 101];
        let mut next = [[0; 2]; 101];

        for price in prices.iter().rev() {
            for i in 1..=k {
                current[i][0] = next[i][0].max(next[i][1] - price);
                current[i][1] = next[i][1].max(next[i - 1][0] + price);

                next[i][0] = current[i][0];
                next[i][1] = current[i][1];
            }
        }

        current[k][0]
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_1() {
        let k = 2;
        let prices = vec![2, 4, 1];
        assert_eq!(Solution::max_profit(k, prices), 2);
    }

    #[test]
    fn test_2() {
        let k = 2;
        let prices = vec![3, 2, 6, 5, 0, 3];
        assert_eq!(Solution::max_profit(k, prices), 7);
    }

    #[test]
    fn test_3() {
        let k = 2;
        let prices = vec![1, 2, 4, 2, 5, 7, 2, 4, 9, 0];
        assert_eq!(Solution::max_profit(k, prices), 13);
    }
}
