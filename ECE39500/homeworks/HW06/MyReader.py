class MyReader:
    def __init__(self, fn):
        self.fileName = fn
        return

    def read(self):
        with open(self.fileName, "r") as f:
            data = f.read()
        num_chars = len(data)
        print(f"\tMyReader:\t {self.fileName} has {num_chars} characters.")
        return None
