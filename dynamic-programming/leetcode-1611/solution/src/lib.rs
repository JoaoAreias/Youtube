#[allow(dead_code)]
struct Solution;

impl Solution {
    #[allow(dead_code)]
    pub fn minimum_one_bit_operations(n: i32) -> i32 {
        match n {
            0 => 0,
            1 => 1,
            _ => {
                let left_bit = 31 - n.leading_zeros() as i32;
                let mask = 0b11 << (left_bit - 1);

                Solution::minimum_one_bit_operations(n ^ mask) + (1 << left_bit)
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_1() {
        assert_eq!(Solution::minimum_one_bit_operations(0), 0);
    }

    #[test]
    fn test_2() {
        assert_eq!(Solution::minimum_one_bit_operations(3), 2);
    }

    #[test]
    fn test_3() {
        assert_eq!(Solution::minimum_one_bit_operations(6), 4);
    }

    #[test]
    fn test_4() {
        assert_eq!(Solution::minimum_one_bit_operations(9), 14);
    }
}
