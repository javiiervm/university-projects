import tkinter as tk

# Dictionary with predefined colors for processes and holes
colors = {
    "P1": "#FF0000",  # Red
    "P2": "#0000FF",  # Blue
    "P3": "#00FF00",  # Green
    "P4": "#FFFF00",  # Yellow
    "P5": "#800080",  # Purple
    "P6": "#FFA500",  # Orange
    "Hole": "#808080"  # Grey
}


# Main drawing function
def window(memoryHistory, MEMORY_SIZE):
    # Create the main window
    root = tk.Tk()
    root.title("Management Memory Simulation")
    root.geometry("1000x800")
    canvas = tk.Canvas(root, width=1000, height=800, bg="white")
    canvas.pack()

    # Initialize variables
    frame_height = 50  # Height of each memory frame (row)
    margin = 80  # Margin from the top/bottom and sides

    # Loop through each time frame in memoryHistory
    for mem_index, memory in enumerate(memoryHistory):
        # Calculate the y-coordinates for this frame
        top = margin + mem_index * (frame_height + 10)
        bottom = top + frame_height
        left = margin + 2

        # Draw the frame label (time)
        canvas.create_text(left - 10, (top + bottom) / 2, text=f"Time {mem_index + 1}", anchor="e")

        # Draw the memory blocks
        for block in memory:
            # Determine the width of the block based on its memory size
            block_width = (block.getMemory() / MEMORY_SIZE) * 800  # Scale to fit the canvas width

            # Assign a color based on the process or hole
            if block.isHole():
                identifier = "Hole"
            else:
                identifier = f"P{block.getProcess()}"

            color = colors.get(identifier, "#000000")  # Default to black if no color is found

            # Draw the block
            canvas.create_rectangle(left, top, left + block_width, bottom, fill=color, outline="black")
            canvas.create_text((left + left + block_width) / 2, (top + bottom) / 2,
                               text=identifier, fill="white" if not block.isHole() else "black")

            # Update the left position for the next block
            left += block_width

    root.mainloop()