use std::rc::Rc;
use std::cell::RefCell;
use crate::tasks::Task;

pub struct Project {
    pub id: i32,
    pub name: String,
    pub tasks: Vec<Rc<RefCell<Task>>>
}

impl Project {
    pub fn new(id: i32, name: String) -> Self {
        Project {
            id: id,
            name: name,
            tasks: Vec::new()
        }
    }

    pub fn addTask(&mut self, task: Rc<RefCell<Task>>) {
        self.tasks.push(task);
    }

    pub fn print(&self) {
        println!("Projekat: {}", self.name);
        for task in &self.tasks {
            task.borrow().print();
        }
    }
}