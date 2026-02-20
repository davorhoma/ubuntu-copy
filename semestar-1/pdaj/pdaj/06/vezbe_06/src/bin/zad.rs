// use std::rc::Rc;
// use std::cell::RefCell;

// #[derive(Clone)]
// struct Node<T> {
//     value: T,
//     next: Option<Box<Node<T>>>,
// }

// struct LinkedList<T> {
//     head: Option<Box<Node<T>>>,
// }


// impl<T> LinkedList<T> {
//     fn new() -> Self {
//         LinkedList {
//             head: None,
//         }
//     }

//     fn push(&mut self, value: T) {
//         let new_node = Box::new(Node {
//             value,
//             next: self.head.take(),
//         });

//         self.head = Some(new_node);
//     }
// }

fn main() {
    // let mut list = LinkedList::new();

    // list.push(3);
    // list.push(2);
    // list.push(1);

    // let mut el = &list.head;
    // loop {
    //     // println!("myList: {}", el.value);
    //     match el {
    //         Some(node) => {
    //             println!("myList: {}", node.value);
    //             el = &Some(*node);
    //         },
    //         None => {
    //             println!("Kraj liste");
    //             break
    //         },
    //     }
    // }

    let mut my_vec: Vec<i32> = vec![];
    my_vec.push(13);
    my_vec.append()

    println!("{:?}", my_vec);
}