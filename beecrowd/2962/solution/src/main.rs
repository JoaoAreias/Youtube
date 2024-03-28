use std::error::Error;
use std::cmp::Ordering;
use std::io;

#[derive(Debug)]
struct UnionFind {
    parent: Vec<usize>,
    rank: Vec<usize>,
}

impl UnionFind {
    pub fn new(n: usize) -> Self {
        UnionFind {
            parent: (0..n).into_iter().collect(),
            rank: vec![0; n],
        }
    }

    pub fn find(&mut self, n: usize) -> Option<usize> {
        match self.parent.get(n) {
            Some(&value) => {
                if n != value {
                    self.parent[n] = self.find(value)?;
                }
                self.parent.get(n).copied()
            }
            None => None
        }
    }

    pub fn union(&mut self, a: usize, b: usize) -> Result<(), String> {
        let parent_a = self.find(a).expect("Could not find `a`");
        let parent_b = self.find(b).expect("Could not find `b`");

        let rank_a = self.rank[parent_a];
        let rank_b = self.rank[parent_b];

        match rank_a.cmp(&rank_b) {
            Ordering::Greater => {
                self.parent[parent_b] = parent_a;
            },
            Ordering::Less => {
                self.parent[parent_a] = parent_b;
            },
            Ordering::Equal => {
                self.parent[parent_b] = parent_a;
                self.rank[parent_a] += 1;
            }
        }

        Ok(())
    }

    pub fn connected(&mut self, a: usize, b: usize) -> Result<bool, String> {
        let parent_a = self.find(a).expect("Could not find `a`");
        let parent_b = self.find(b).expect("Could not find `b`");

        return Ok(parent_a == parent_b);
    }
}

fn parse_line(line: Result<String, io::Error>) -> (i64, i64, i64) {
    match line {
        Err(e) => panic!("Error reading line: {}", e),
        Ok(line) => {
            let values: Vec<_> = line
                .split_whitespace()
                .map(|x| {
                    x.parse()
                        .expect("Input should only contain non-negative Integers")
                })
                .collect();

            (values[0], values[1], values[2])
        }
    }
}

fn dist(p1: &[i64], p2: &[i64]) -> f64 {
    (((p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[1]) * (p1[1] - p2[1])) as f64).sqrt()
}

fn main() -> Result<(), Box<dyn Error>> {
    let mut lines = io::stdin().lines();
    let (m, n, k) = parse_line(lines.next().expect("Input cannot be empty"));
    let mut union_find = UnionFind::new((k + 4) as usize);
    let mut sensors = vec![vec![0; 3]; k as usize];

    for (i, line) in lines.enumerate() {
        (sensors[i][0], sensors[i][1], sensors[i][2]) = parse_line(line);

        // Sensor encherga a parede de cima
        if sensors[i][1] + sensors[i][2] >= n {
            union_find.union(0, i + 4)?;
        }

        // Sensor encherga a parede da direita
        if sensors[i][0] + sensors[i][2] >= m {
            union_find.union(1, i + 4)?;
        }

        // Sensor encherga a parede de baixo
        if sensors[i][1] - sensors[i][2] <= 0 {
            union_find.union(2, i + 4)?;
        }

        // Sensor encherga a parede da esquerda
        if sensors[i][0] - sensors[i][2] <= 0 {
            union_find.union(3, i + 4)?;
        }
    }

    for (i, sensor_i) in sensors.iter().enumerate() {
        for (j, sensor_j) in sensors.iter().enumerate().skip(i + 1) {
            if dist(sensor_i, sensor_j) <= (sensor_i[2] + sensor_j[2]) as f64 {
                union_find.union(i + 4, j + 4)?;
            }
        }
    }

    if union_find.connected(0, 1)?
        || union_find.connected(0, 2)?
        || union_find.connected(3, 1)?
        || union_find.connected(3, 2)?
    {
        println!("N");
    } else {
        println!("S");
    }
    Ok(())
}
