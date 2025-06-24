Library Management System
A simple command-line based Library Management System written in C++, designed for students and librarians to manage book records and borrowing activities.

 Features:
 1)Student Functionality
  - Issue a book (with 14-day return policy)
  - Return a book (calculates fine for late returns)
  - View available books
 2)Librarian Functionality
  - Add new books to the library
  - View all books in the system
 3)Data Persistence
  - Book data is saved in a local text file ('books.txt')
  - Ensures book records remain even after program is closed

Technologies Used:
- C++
- File Handling ('fstream')
- Object-Oriented Programming (OOP)

OOP Concepts Demonstrated
- Classes and Objects
- Inheritance ('Student' and 'Librarian' inherit from 'User')
- Encapsulation
- Polymorphism(via 'showUserType()' virtual function)
- Abstraction

