extends Sprite


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

# Called when the node enters the scene tree for the first time.
func _ready():
	var a =5

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
func _process(delta):
	print(get_rotation())
	
