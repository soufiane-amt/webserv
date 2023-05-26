# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    todo.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 15:46:02 by fech-cha          #+#    #+#              #
#    Updated: 2023/05/25 19:41:45 by fech-cha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/python

import cgitb
cgitb.enable()

import cgi

# Function to generate the HTML form for input
def generate_input_form():
    print("""
        <form method="post" action="todo.py">
            <label for="name">Name:</label>
            <input type="text" name="name" id="name"><br>
            <label for="task">Task:</label>
            <input type="text" name="task" id="task"><br>
            <input type="submit" value="Add to List">
        </form>
    """)

# Function to generate the HTML representation of the to-do list
def generate_todo_list(name, tasks):
    print(f"<h2>To-Do List for {name}</h2>")
    if tasks:
        print("<ul>")
        for task in tasks:
            print(f"<li>{task}</li>")
        print("</ul>")
    else:
        print("<p>No tasks added yet.</p>")

# Function to parse the form data and update the to-do list
def update_todo_list(name, task):
    with open("todo.txt", "a") as file:
        file.write(f"{name}: {task}\n")

# Main CGI script
if __name__ == "__main__":
    # Get form data
    form = cgi.FieldStorage()
    name = form.getvalue("name")
    task = form.getvalue("task")

    # Set content type
    print("Content-type: text/html\r\n\r\n")
    print("\r\n")
    print ("<html>")
    print ("<head>")
    print ("<title>To do list cgi script</title>")
    print ("</head>")
    print ("<body>")

    # Load existing to-do list
    tasks = []
    try:
        with open("todo.txt", "r") as file:
            #read content of the file
            content = file.readlines()
            for line in file:
                if line not in content:
                    with open("todo.txt", "a") as file:
                        if line:
                            tasks.append(line);
    except IOError:
        pass

    # Update to-do list if form data is provided
    if name and task:
        update_todo_list(name, task)

    # Generate HTML response
    generate_input_form()
    generate_todo_list(name, tasks)

    print ("</body>")
    print ("</html>")