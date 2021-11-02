from tkinter import *

#creating root window
root = Tk()

# Text entry box
#e = Entry(root, width=50)
#e.pack()

# Funktion
def add():
    entrybox_task.insert(0, END)
    entrybox_task.delete(0, END)

def clear():
    entrybox_task.delete(0, END)
    entrybox_date.delete(0, END)

#Output field
output_field = Text(root, height=50, width=65)


# Text entry
entrybox_task = Entry(root, width=32)
entrybox_date = Entry(root, width=15)

# Button
button_add = Button(root, text="ADD", padx=40, pady=10, state=DISABLED)
button_del = Button(root, text="DELETE", padx=40, pady=10, state=DISABLED)
button_save = Button(root, text="SAVE", padx=40, pady=10, state=DISABLED)
button_load = Button(root, text="LOAD", padx=40, pady=10, state=DISABLED)
button_submit = Button(root, text="SUBMIT", padx=7, state=DISABLED)
button_clear = Button(root, text="CLEAR", padx=7, command=clear)

# Put the Buttons on the screen
button_add.grid(row=9, column=0)
button_del.grid(row=9, column=1)
button_save.grid(row=9, column=2)
button_load.grid(row=9, column=3, columnspan=2)
button_submit.grid(row=8, column=3)
button_clear.grid(row=8, column=4)

# Put the entrybox on the screen
entrybox_task.grid(row=8, column=0, columnspan=2)
entrybox_date.grid(row=8, column=2, columnspan=1)

# Output_field grid
output_field.grid(row=0, column=0, columnspan=5)

#start the main events loop
root.mainloop()