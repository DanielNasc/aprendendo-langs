use rand::{thread_rng, Rng};

// sample space: all possible outcomes of an experiment
// random variable: a function that maps each outcome of an experiment to a real number
// probability mass function: a function that maps each outcome of an experiment to a probability
// expected value: the average of the random variable

fn expected_value(sample_space: &Vec<i32>, random_variable: &dyn Fn(i32) -> f64, pmf: &dyn Fn(i32) -> f64) -> f64 {
    let mut sum = 0.0;

    for outcome in sample_space {
        sum += random_variable(*outcome) as f64 * pmf(*outcome);
    }

    sum
}

fn strong_law_of_large_numbers(
        sample_space: &Vec<i32>,
        random_variable: &dyn Fn(i32) -> f64,
        tries: i32
) -> f64 {
    let mut sum = 0.0;

    for _ in 0..tries {
        let outcome = sample_space[thread_rng().gen_range(0..sample_space.len())];
        sum += random_variable(outcome) as f64;
    }

    sum / tries as f64
}

fn variance1(
        sample_space: &Vec<i32>,
        random_variable: &dyn Fn(i32) -> f64,
        pmf: &dyn Fn(i32) -> f64
) -> f64 {
    let random_variable_minus_expected_value = |x: i32| random_variable(x) as f64 - expected_value(sample_space, random_variable, pmf);

    expected_value(sample_space, &|x: i32| random_variable_minus_expected_value(x).powi(2), pmf)
}

fn variance2(
    sample_space: &Vec<i32>,
    random_variable: &dyn Fn(i32) -> f64,
    pmf: &dyn Fn(i32) -> f64
) -> f64 {
    expected_value(sample_space, &|x: i32| random_variable(x).powi(2), pmf) - expected_value(sample_space, random_variable, pmf).powi(2)
}

fn main() {
    let sample_space = vec![1, 2, 3, 4, 5, 6];
    let random_variable = |x: i32| x as f64;
    let pmf = |_: i32| 1.0 / 6.0;

    println!("Expected value: {}", expected_value(&sample_space, &random_variable, &pmf));
    println!("Strong law of large numbers (100): {}", strong_law_of_large_numbers(&sample_space, &random_variable, 100));
    println!("Strong law of large numbers (1000): {}", strong_law_of_large_numbers(&sample_space, &random_variable, 1000));
    println!("Strong law of large numbers (10000): {}", strong_law_of_large_numbers(&sample_space, &random_variable, 10000));
    println!("Strong law of large numbers (100000): {}", strong_law_of_large_numbers(&sample_space, &random_variable, 100000));
    println!("Strong law of large numbers (1000000): {}", strong_law_of_large_numbers(&sample_space, &random_variable, 1000000));
    println!("Variance1: {}", variance1(&sample_space, &random_variable, &pmf));
    println!("Variance2: {}", variance2(&sample_space, &random_variable, &pmf));
}
