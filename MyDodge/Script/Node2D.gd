extends Node2D


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
var data = preload("res://native/gdnative/GDMenuTouch.gdns").new()
onready var sceneMenu = preload("res://scenes/menu/MenuTouch.tscn")
# Called when the node enters the scene tree for the first time.
func _ready():
	var menu = sceneMenu.instance()
	set_script(menu)
	add_child(menu)
	menu._button_down()
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
