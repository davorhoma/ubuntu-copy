todo_list = []

def show_menu():
    print("\nTo-Do List:")
    print("1. Add Task")
    print("2. View Tasks")
    print("3. Exit")

def add_task():
    task = input("Enter a task: ")
    todo_list.append(task)
    print(f"'{task}' added to the list.")

def view_tasks():
    if not todo_list:
        print("Your to-do list is empty.")
    else:
        print("\nYour To-Do List:")
        for i, task in enumerate(todo_list, 1):
            print(f"{i}. {task}")

if __name__ == "__main__":
    while True:
        show_menu()
        choice = input("Choose an option: ")
        if choice == "1":
            add_task()
        elif choice == "2":
            view_tasks()
        elif choice == "3":
            print("Goodbye!")
            break
        else:
            print("Invalid choice. Please try again.")
