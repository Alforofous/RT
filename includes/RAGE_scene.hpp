#pragma once

#include "RAGE_object.hpp"
#include <vector>

class RAGE;

class RAGE_scene
{
public:
	RAGE_scene(const char *name = "New Scene");

	void draw();
	bool add_object(RAGE_object *object);
	std::vector<RAGE_object *> *get_objects();
	std::vector<RAGE_object *> *get_selected_objects();
	void select_all_objects();
	bool load_from_GLB(const char *path);

private:
	nlohmann::json read_scene_info_GLB(nlohmann::json &json);
	void read_scene_nodes_GLB(nlohmann::json &json, nlohmann::json &json_scene);
	void process_children(nlohmann::json &json, nlohmann::json &node, RAGE_object *parent);
	void delete_objects();
	RAGE_object *read_scene_node_GLB(nlohmann::json &node);
	std::string name;
	std::vector<RAGE_object *> objects;
	std::vector<RAGE_object *> selected_objects;
};