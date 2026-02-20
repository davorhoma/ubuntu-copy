// Davor Homa E2 53/2025
use std::rc::Rc;
use std::cell::RefCell;
use std::io;

use kolokvijum_v2::tasks::Task;
use kolokvijum_v2::tasks::State;
use kolokvijum_v2::project::Project;
use kolokvijum_v2::user::User;

fn main() {
    let mut tasks: Vec<Rc<RefCell<Task>>> = Vec::new();
    let mut task = Rc::new(RefCell::new(Task::new(32, String::from("Dizajn interfejsa"))));
    tasks.push(Rc::clone(&task));
    // task.borrow().print();
    
    // task.borrow_mut().startTask();
    // task.borrow().print();

    // task.borrow_mut().finishTask(String::from("Verzija 1 zavrsena"));
    // task.borrow().print();

    let mut task2 = Rc::new(RefCell::new(Task::new(33, String::from("Implementacija pozadine"))));
    tasks.push(Rc::clone(&task2));

    println!("---------------- Pre zapocinjanja zadataka: ----------------\n");

    let mut project = Project::new(11, String::from("Projekat Alfa"));
    project.addTask(Rc::clone(&task));
    project.addTask(Rc::clone(&task2));
    project.print();


    println!("");
    let mut user = User::new(13, String::from("Ana"));
    user.addTask(Rc::clone(&task));
    user.print();

    task.borrow_mut().finishTask(String::from("Verzija 1 zavrsena"));
    // task2.borrow_mut().startTask();
    println!("\n---------------- Nakon zavrsetka zadataka ----------------\n");

    project.print();
    println!("");
    user.print();

    loop {
        println!("\n---------------- OPCIJE ----------------");
        println!("1 - Rukovanje zadacima");
        println!("2 - Rukovanje projektima");
        println!("3 - Rukovanje korisnicima");
        println!("X - Izlaz");
    
        let mut input = String::new();
        match io::stdin().read_line(&mut input) {
            Ok(_) => {
                println!("{}", input);
                match input.trim() {
                    "1" => rukovanje_zadacima(&mut tasks),
                    "2" => rukovanje_projektima(),
                    "3" => rukovanje_korisnicima(),
                    "X" | "x" => break,
                    _ => continue,
                }
            },
            Err(e) => eprintln!("ERROR: {}", e),
        }
    }
}

fn rukovanje_zadacima(tasks: &mut Vec<Rc<RefCell<Task>>>) {
    println!("\n---------------- ZADACI ----------------");
    loop {
        println!("1 - Dodaj zadatak");
        println!("2 - Pokreni zadatak");
        println!("3 - Zavrsi zadatak");
        println!("4 - Ispisi zadatak");
        println!("X - Izlaz");
    
        let mut input = String::new();
        match io::stdin().read_line(&mut input) {
            Ok(_) => {
                println!("{}", input);
                match input.trim() {
                    "1" => newTask(tasks),
                    "2" => startTask(tasks),
                    // "3" => endTask(tasks),
                    "4" => printTask(tasks),
                    "X" | "x" => break,
                    _ => continue,
                }
            },
            Err(e) => eprintln!("ERROR: {}", e),
        }
    }
}

fn newTask(tasks: &mut Vec<Rc<RefCell<Task>>>) {
    println!("Id: ");
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read lline");
    let id: i32 = input.trim().parse().expect("Please type a number!");

    input.clear();
    io::stdin().read_line(&mut input).expect("Failed to read lline");
    let name = input.trim();

    let newTask = Rc::new(RefCell::new(Task::new(id, name.to_string())));
    tasks.push(newTask);
}

fn startTask(tasks: &mut Vec<Rc<RefCell<Task>>>) {
    println!("Id: ");
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read lline");
    let id: i32 = input.trim().parse().expect("Please type a number!");

    match tasks.iter().find(|&t| t.borrow().id == id) {
        Some(task) => {
            task.borrow_mut().startTask();
            task.borrow().print();
        }
        _ => println!("Task with id {} not found", id),
    }
}

fn printTask(tasks: &mut Vec<Rc<RefCell<Task>>>) {
    println!("Id: ");
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read lline");
    let id: i32 = input.trim().parse().expect("Please type a number!");

    match tasks.iter().find(|&t| t.borrow().id == id) {
        Some(task) => task.borrow().print(),
        _ => println!("Task with id {} not found", id),
    }
}

fn rukovanje_projektima() {

}

fn rukovanje_korisnicima() {

}