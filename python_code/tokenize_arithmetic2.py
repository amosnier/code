OPERATORS = '+', '-', '*', '/'

class Tokenizer:
    def __init__(self, expression):
        self.expression = expression
        self.token_ready = False
        self.token = None
        self.char_consumed = True
        self.state = self.state_none

    def state_none(self, c):
        if c.isdecimal():
            self.token = c
            self.state = self.state_number
        elif c in OPERATORS:
            self.token = 'operator', c
            self.token_ready = True
    
    def state_number(self, c):
        if c.isdecimal():
            self.token += c
        else:
            self.char_consumed = False
            self.token = 'number', self.token
            self.token_ready = True
            self.state = self.state_none

    def interpret_character(self, c):
        self.token_ready = False
        self.char_consumed = True
        self.state(c)
        
    def __call__(self):
        for c in self.expression:
            self.char_consumed = False
            while not self.char_consumed:
                self.interpret_character(c)
                if self.token_ready:
                    yield self.token
        if self.state == self.state_number:
            yield 'number', self.token

def main():
    for x in Tokenizer('15+ 2 * 378 / 5')():
        print(x)

    # ('number', '15')
    # ('operator', '+')
    # ('number', '2')
    # ('operator', '*')
    # ('number', '378')
    # ('operator', '/')
    # ('number', '5')

if __name__ == "__main__":
    main()
