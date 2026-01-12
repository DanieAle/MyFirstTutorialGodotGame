extends Node


# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.


func _ready():
	var lib_path = "res://bin/armv7/libAndroid_armv7.so"
	var library = Engine.get_singleton("NativeLibrary")
	if not library:
		push_error("El módulo NativeLibrary no está disponible.")
		return
	var result = library.open(lib_path)
	if result != OK:
		push_error("Error al cargar la librería nativa: " + str(result))
		return

	# Llama a una función de inicialización si es necesario
	var init_func = library.get_symbol_address("initialize_native")
	if init_func:
		var init_result = lib_func(init_func)
		if init_result != OK:
			push_error("Error al llamar a la función de inicialización de la librería nativa.")

	# Llama a una función de inicialización si es necesario
# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
