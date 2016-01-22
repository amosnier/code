import tkinter as tk


class App:
    def __init__(self, master):
        frame = tk.Frame(master)
        frame.pack()

        self.file_text = tk.Text(frame)
        self.file_text.pack()

        self.console_text = tk.Text(frame)
        self.console_text.pack()

root = tk.Tk()

app = App(root)

root.mainloop()
