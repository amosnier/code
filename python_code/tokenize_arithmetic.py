OPERATORS = '+', '-', '*', '/'

def tokenize(expression):
    def state_none(c):
        if c.isdecimal():
            self.token = c
            self.state = state_number
        elif c in OPERATORS:
            self.token = 'operator', c
            self.token_ready = True
    
    def state_number(c):
        if c.isdecimal():
            self.token += c
        else:
            self.char_consumed = False
            self.token = 'number', self.token
            self.token_ready = True
            self.state = state_none

    def interpret_character(c):
        self.token_ready = False
        self.char_consumed = True
        self.state(c)
        
    class self:
        token_ready = False
        token = None
        char_consumed = True
        state = state_none

    for c in expression:
        self.char_consumed = False
        while not self.char_consumed:
            interpret_character(c)
            if self.token_ready:
                yield self.token
    if self.state == state_number:
        yield 'number', self.token

def main():
    for x in tokenize('15+ 2 * 378 / 5'):
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
