import tkinter as tk

class LEDInterface:
    def __init__(self, root):
        self.root = root
        self.root.title("Control de LED")
        self.root.configure(bg="#f0f0f0")

        self.led_state = False

        self.led_label = tk.Label(root, text="LED Apagado", font=('Helvetica', 18), bg="#f0f0f0")
        self.led_label.pack(pady=20)

        self.toggle_button = tk.Button(root, text="Encender LED", font=('Helvetica', 14), command=self.toggle_led, bg="#4caf50", fg="white", padx=20, pady=10)
        self.toggle_button.pack(pady=10)

    def toggle_led(self):
        if self.led_state:
            self.led_state = False
            self.led_label.config(text="LED Apagado")
            # Aquí iría el código para enviar la señal al Arduino para apagar el LED
        else:
            self.led_state = True
            self.led_label.config(text="LED Encendido")
            # Aquí iría el código para enviar la señal al Arduino para encender el LED

if __name__ == "__main__":
    root = tk.Tk()
    app = LEDInterface(root)
    root.mainloop()


    