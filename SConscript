import os

sources = {}

Import("c_state_env")

objects = [c_state_env.Object(x) for x in Glob("./src/*.c")]

path = Dir('.').srcnode().abspath
result = (objects, list(map(lambda x: os.path.join(path, x), ["src"])))
Return("result")
