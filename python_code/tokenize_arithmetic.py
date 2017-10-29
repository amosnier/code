OPERATORS = '+', '-', '*', '/'

def tokenize(expression):
    def token_state_none(c):
        if c.isdecimal():
            state.token = c
            state.token_state = token_state_number
        elif c in OPERATORS:
            state.token = 'operator', c
            state.token_ready = True
    
    def token_state_number(c):
        if c.isdecimal():
            state.token += c
        else:
            state.char_consumed = False
            state.token = 'number', state.token
            state.token_ready = True
            state.token_state = token_state_none

    def interpret_character(c):
        state.token_ready = False
        state.char_consumed = True
        state.token_state(c)
        
    class state:
        token_ready = False
        token = None
        char_consumed = True
        token_state = token_state_none

    expression += ' ' # terminator for the last token in the expression
    for c in expression:
        state.char_consumed = False
        while not state.char_consumed:
            interpret_character(c)
            if state.token_ready:
                yield state.token

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
