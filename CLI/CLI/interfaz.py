"""
This module initializes and manages the GUI for the project.
It sets up the main application window, displays the camera feed, 
shows event messages, and handles UI components.
"""
import tkinter as tk
from PIL import Image, ImageTk
import datetime

# Global variable for the main application window
WINDOW = tk.Tk()

def windowInit():
    """
    Initializes the main application window.

    - Sets the window title and background color.
    - Configures the window size and prevents excessive resizing.
    - Defines the grid layout for UI elements.

    Returns:
        None
    """
    #WINDOW = tk.Tk()
    WINDOW.title("MAW")
    WINDOW.resizable(1, 1)
    WINDOW.minsize(1080, 720)
    WINDOW.configure(bg="darkgrey")
    WINDOW.columnconfigure(0, weight=6)
    WINDOW.columnconfigure(1, weight=4)
    WINDOW.rowconfigure(0, weight=2)
    WINDOW.rowconfigure(1, weight=8)


def cargar_y_mostrar_imagen():
    """
    Loads and displays the application logo.

    - Loads an image from the file system.
    - Resizes it to fit within a specified area.
    - Displays the image within the UI.

    Returns:
        None
    """
    img = Image.open("LOGO.png")
    max_width = 280
    max_height = 216
    img.thumbnail((max_width, max_height))
    
    imagen = ImageTk.PhotoImage(img)
    LOGO_LABEL = tk.Label(image=imagen, anchor="center", bg="darkgrey")
    LOGO_LABEL.image = imagen   # Keep a reference of the image

    # Set the maximum size for the column and row
    LOGO_LABEL.grid(row=0, column=1, sticky="nsew")
    LOGO_LABEL.grid_rowconfigure(0, weight=1)
    LOGO_LABEL.grid_columnconfigure(1, weight=1)


def windowsGrid():
    """
    Creates and configures the main UI layout.

    - Displays the camera feed area.
    - Loads and places the application logo.
    - Sets up a terminal for event logging.
    - Adds a scrollbar for message navigation.

    Returns:
        None
    """
    img=Image.open("not_signal.jpg")
    #img.thumbnail((768,432))
    #img.resize((68,20))
    imagen=ImageTk.PhotoImage(img)
    global CAMERA_LABEL
    CAMERA_LABEL = tk.Label(image=imagen,width=768, height=432, anchor="center",bg="black")
    CAMERA_LABEL.image = imagen  
    CAMERA_LABEL.grid(row=0, column=0,rowspan=2, sticky="nsew")
 
   
    # Logo
    cargar_y_mostrar_imagen()

    # Terminal Frame
    TERMINAL_FRAME = tk.Frame(WINDOW, bg="darkgrey")
    TERMINAL_FRAME.grid(row=1, column=1, rowspan=2, sticky="nsew")
    TERMINAL_FRAME.columnconfigure(1, weight=4)
    TERMINAL_FRAME.rowconfigure(1, weight=7)
    TERMINAL_LABEL = tk.Label(TERMINAL_FRAME, text="Event Monitor", bg="#E65D0E", fg="black", anchor="center", font=("Verdana", 20, "bold"))
    TERMINAL_LABEL.grid(row=0, column=0, sticky="nsew",columnspan=2)
    TERMINAL_LABEL.grid_columnconfigure(0, weight=1)
    TERMINAL_LABEL.grid_rowconfigure(0, weight=1)
    TERNMINAL_EVENTS = tk.Frame(TERMINAL_FRAME, bg="black",border=1, borderwidth=1)
    TERNMINAL_EVENTS.grid(row=1, column=1, sticky="nsew")

    #Area terminal
    global TERMINAL_TEXT
    TERMINAL_TEXT = tk.Text(TERNMINAL_EVENTS, bg="black", fg="white", font=("Consolas", 12),  wrap=tk.WORD)
    TERMINAL_TEXT.grid(row=0, column=0, sticky="nsew")
    TERMINAL_TEXT.tag_configure("error", foreground="red", font=("Verdana", 12, "bold"))
    TERMINAL_TEXT.tag_configure("warning", foreground="yellow", font=("Verdana", 12, "bold"))
    TERMINAL_TEXT.tag_configure("success", foreground="green", font=("Verdana", 12, "bold"))
    TERMINAL_TEXT.tag_configure("normal", foreground="white", font=("Verdana", 12, "normal"))
    TERMINAL_TEXT.tag_configure("timestamp", foreground="gray", font=("Verdana", 10, "normal"))
    TERMINAL_TEXT.tag_configure("process", foreground="#FF00EF", font=("Verdana", 12, "bold"))
    TERMINAL_TEXT.tag_configure("incoming", foreground="#00FFFF", font=("Verdana", 12, "bold"))
    # Scrollbar
    
    TERMINAL_SCROLLBAR = tk.Scrollbar(TERNMINAL_EVENTS, command=TERMINAL_TEXT.yview)
    TERMINAL_SCROLLBAR.grid(row=0, column=1, sticky="nsew")
    TERMINAL_TEXT["yscrollcommand"] = TERMINAL_SCROLLBAR.set


def add_message(message,style=None):
    """
    Adds a message to the terminal.

    Args:
        message (str): The message to display.
        style (str, optional): The style tag for the message.

    Returns:
        None
    """
    timestamp = datetime.datetime.now().strftime("%H:%M:%S")  
    TERMINAL_TEXT.insert(tk.END, timestamp + " - ")
    TERMINAL_TEXT.insert(tk.END, message + "\n", style)
    TERMINAL_TEXT.see(tk.END)


def update_camera(image):
    """
    Updates the camera feed display.

    Args:
        image (ImageTk.PhotoImage): The image to display in the camera feed.

    Returns:
        None
    """
    CAMERA_LABEL.configure(image=image)
    CAMERA_LABEL.image = image