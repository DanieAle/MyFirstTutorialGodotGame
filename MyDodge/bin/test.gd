extends Sprite


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

# Called when the node enters the scene tree for the first time.
func _ready():
	# Recorrer todos los hijos del nodo actual
	var num_hijos = get_child_count()
	for i in range(num_hijos):
		var hijo = get_child(i)
	# Realizar acciones en función del hijo actual
	# Por ejemplo, imprimir el nombre del nodo hijo y su índice
		print("Hijo", i, ":", hijo.get_name())
	
	# Puedes hacer más cosas con el nodo hijo, como acceder a sus propiedades o ejecutar métodos
	# Por ejemplo, si el hijo tiene un script con una función "mi_funcion", puedes llamarla así:
		if hijo.has_method("mi_funcion"):
			hijo.mi_funcion()


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
