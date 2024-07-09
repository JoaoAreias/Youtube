struct Solution;

impl Solution {
    pub fn max_profit(prices: Vec<i32>) -> i32 {
        let mut profit = 0;
        let mut last_price = prices[0];

        for price in prices {
            if price > last_price {
                profit += price - last_price;
            }
            last_price = price;
        }
        profit
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_1() {
        let prices = vec![7, 1, 5, 3, 6, 4];
        assert_eq!(Solution::max_profit(prices), 7);
    }

    #[test]
    fn test_2() {
        let prices = vec![1, 2, 3, 4, 5];
        assert_eq!(Solution::max_profit(prices), 4);
    }

    #[test]
    fn test_3() {
        let prices = vec![7, 6, 4, 3, 1];
        assert_eq!(Solution::max_profit(prices), 0);
    }
}
