OPERATORS = '+', '-', '*', '/'

class Tokenizer:
    def __init__(self, expression):
        self.token = None
        self.char_consumed = True
        self.state = Tokenizer._state_none
        self.expression = iter(expression)

    def __iter__(self):
        return self
        
    def _state_none(self, c):
        if c.isdecimal():
            self.token = c
            self.state = Tokenizer._state_number
        elif c in OPERATORS:
            return 'operator', c
    
    def _state_number(self, c):
        if c.isdecimal():
            self.token += c
        else:
            self.char_consumed = False
            self.state = Tokenizer._state_none
            return 'number', self.token

    def _interpret_character(self, c):
        self.char_consumed = True
        return self.state(self, c)
        
    def __next__(self):
        for c in self.expression:
            self.char_consumed = False
            while not self.char_consumed:
                token = self._interpret_character(c)
                if token:
                    return token
        token = self._interpret_character('')
        if token:
            return token
        raise StopIteration

def main():
    for x in Tokenizer('15+ 2 * 378 / 5'):
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
