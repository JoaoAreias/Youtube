use std::cmp::Ordering;
use std::error::Error;
use std::io;

fn parse_teams_solutions(line: Result<String, io::Error>) -> Result<(usize, usize, usize), String> {
    let binding = line.expect("Failed to read line");
    let problems = binding.split_whitespace();

    let (mut a, mut b, mut solved) = (0, 0, 0);
    for problem in problems {
        let values: Vec<_> = problem
            .split('/')
            .map(|item| item.parse::<usize>())
            .collect();
        match values.as_slice() {
            [Ok(tries), Ok(time)] => {
                a += tries - 1;
                b += time;
                solved += 1;
            }
            [Ok(_), Err(_)] => continue,
            _ => return Err("Invalid Input".to_string()),
        }
    }
    Ok((a, b, solved))
}

fn parse_first_line(line: Result<String, io::Error>) -> Result<(usize, usize), String> {
    let binding = line.expect("Failed to read line");
    let values: Vec<_> = binding
        .split_whitespace()
        .map(|item| item.parse::<usize>())
        .collect();

    match values.as_slice() {
        [Ok(t), Ok(p)] => Ok((*t, *p)),
        _ => Err("Invalid Input".to_string()),
    }
}

fn main() -> Result<(), Box<dyn Error>> {
    let mut lines = io::stdin().lines();
    let mut score: Vec<Vec<_>> = vec![Vec::new(); 11];
    let mut penalties = [[0; 2]; 100];

    let (mut t, mut p) =
        parse_first_line(lines.next().expect("Unexpected EOF")).expect("Invalid Input");

    while t != 0 && p != 0 {
        for i in 0..11 {
            score[i].clear();
        }
        for team in 0..t {
            let (a, b, solved) = parse_teams_solutions(lines.next().expect("Unexpected EOF"))?;
            penalties[team][0] = a as i32;
            penalties[team][1] = b as i32;
            score[solved].push((20 * a + b, team));
        }

        let (mut lb, mut ub) = (1, 4000);
        let mut break_all = false;

        for i in 0..11 {
            if break_all {
                break;
            }
            score[i].sort_unstable();

            for window in score[i].windows(2) {
                let (t1, t2) = (window[0].1, window[1].1);
                let (a1, b1) = (penalties[t1][0], penalties[t1][1]);
                let (a2, b2) = (penalties[t2][0], penalties[t2][1]);

                if a1 == a2 {
                    continue;
                }

                let ep = (b2 - b1) / (a1 - a2);
                match ep.cmp(&20) {
                    Ordering::Less => {
                        lb = lb.max(ep + 1);
                    }
                    Ordering::Greater => {
                        ub = ub.min(if (b2 - b1) % (a1 - a2) == 0 {
                            ep - 1
                        } else {
                            ep
                        })
                    }
                    Ordering::Equal => {
                        if (b2 - b1) % (a1 - a2) == 0 {
                            (ub, lb) = (20, 20);
                            break_all = true;
                        } else {
                            ub = 20;
                        }
                    }
                }
            }
        }

        if ub == 4000 {
            println!("{} *", lb);
        } else {
            println!("{} {}", lb, ub);
        }

        (t, p) = parse_first_line(lines.next().expect("Unexpected EOF")).expect("Invalid Input");
    }

    Ok(())
}
