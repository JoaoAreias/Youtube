struct Solution;

impl Solution {
    pub fn max_profit(prices: Vec<i32>) -> i32 {
        let mut smallest_so_far = i32::MAX;
        let mut max_profit = 0;

        for price in prices.into_iter() {
            if price < smallest_so_far {
                smallest_so_far = price;
            } else {
                let profit = price - smallest_so_far;
                if profit > max_profit {
                    max_profit = profit;
                }
            }
        }

        max_profit
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_1() {
        let prices = vec![7, 1, 5, 3, 6, 4];
        let result = Solution::max_profit(prices);
        assert_eq!(result, 5);
    }

    #[test]
    fn test_2() {
        let prices = vec![7, 6, 4, 3, 1];
        let result = Solution::max_profit(prices);
        assert_eq!(result, 0);
    }
}
