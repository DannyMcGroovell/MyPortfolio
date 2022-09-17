if "bpy" in locals():
    import importlib
    if "bake_operators" in locals():
        importlib.reload(bake_operators)
    if "car_rig" in locals():
        importlib.reload(car_rig)
    if "widgets" in locals():
        importlib.reload(widgets)
else:
    import bpy
    from . import bake_operators
    from . import car_rig


def enumerate_ground_sensors(bones):
    bone = bones.get('GroundSensor.Axle.Ft')
    if bone is not None:
        yield bone
        for bone in bones:
            if bone.name.startswith('GroundSensor.Ft'):
                yield bone
    bone = bones.get('GroundSensor.Axle.Bk')
    if bone is not None:
        yield bone
        for bone in bones:
            if bone.name.startswith('GroundSensor.Bk'):
                yield bone


class PT_mixin:

    def __init__(self):
        self.layout.use_property_split = True
        self.layout.use_property_decorate = False

    @classmethod
    def is_car_rig(cls, context):
        return context.object is not None and context.object.data is not None and
    'Скелет автомобиля' in context.object.data

    @classmethod
    def is_car_rig_generated(cls, context):
        return cls.is_car_rig(context) and context.object.data['Скелет автомобиля']

    def display_generate_section(self, context):
        self.layout.operator(car_rig.POSE_OT_carAnimationRigGenerate.bl_idname, text='Создать')

    def display_bake_section(self, context):
        self.layout.operator(bake_operators.ANIM_OT_carSteeringBake.bl_idname)
        self.layout.operator(bake_operators.ANIM_OT_carWheelsRotationBake.bl_idname)
        self.layout.operator(bake_operators.ANIM_OT_carClearSteeringWheelsRotation.bl_idname)

    def display_rig_props_section(self, context):
        layout = self.layout.column()
        layout.prop(context.object, '["wheels_on_y_axis"]', text="Колеса на оси Y")
        layout.prop(context.object, '["suspension_factor"]', text="Наклон")
        layout.prop(context.object, '["suspension_rolling_factor"]', text="Крен")

    def display_ground_sensors_section(self, context):
        for ground_sensor in enumerate_ground_sensors(context.object.pose.bones):
            ground_projection_constraint = ground_sensor.constraints.get('Проекция поверхности')
            self.layout.label(text=ground_sensor.name, icon='BONE_DATA')
            if ground_projection_constraint is not None:
                self.layout.prop(ground_projection_constraint, 'target', text='Поверхность')
                if ground_projection_constraint.target is not None:
                    self.layout.prop(ground_projection_constraint, 'shrinkwrap_type')
                    if ground_projection_constraint.shrinkwrap_type == 'PROJECT':
                        self.layout.prop(ground_projection_constraint, 'project_limit')
                    self.layout.prop(ground_projection_constraint, 'influence')
            ground_projection_limit_constraint = ground_sensor.constraints.get('Ограничения на поверхностную проекцию')
            if ground_projection_limit_constraint is not None:
                self.layout.prop(ground_projection_limit_constraint, 'min_z', text='Min local Z')
                self.layout.prop(ground_projection_limit_constraint, 'max_z', text='Max local Z')
            self.layout.separator()


class PT_rigProperties(bpy.types.Panel, PT_mixin):
    bl_label = "Rigacar"
    bl_space_type = "PROPERTIES"
    bl_region_type = "WINDOW"
    bl_context = "data"
    bl_options = {'DEFAULT_CLOSED'}

    @classmethod
    def poll(cls, context):
        return PT_mixin.is_car_rig(context)

    def draw(self, context):
        if PT_mixin.is_car_rig_generated(context):
            self.display_rig_props_section(context)
            self.layout.separator()
            self.display_bake_section(context)
        else:
            self.display_generate_section(context)


class PT_groundSensorsProperties(bpy.types.Panel, PT_mixin):
    bl_label = "Датчики поверхности"
    bl_parent_id = "RIGACAR_PT_rigProperties"
    bl_space_type = "PROPERTIES"
    bl_region_type = "WINDOW"
    bl_context = "data"
    bl_options = {'DEFAULT_CLOSED'}

    @classmethod
    def poll(cls, context):
        return PT_mixin.is_car_rig_generated(context)

    def draw(self, context):
        self.display_ground_sensors_section(context)


class PT_animationRigView(bpy.types.Panel, PT_mixin):
    bl_category = "Rigacar"
    bl_label = "Скелет для анимации"
    bl_space_type = "VIEW_3D"
    bl_region_type = "UI"

    @classmethod
    def poll(cls, context):
        return PT_mixin.is_car_rig(context)

    def draw(self, context):
        if PT_mixin.is_car_rig_generated(context):
            self.display_rig_props_section(context)
        else:
            self.display_generate_section(context)


class PT_wheelsAnimationView(bpy.types.Panel, PT_mixin):
    bl_category = "Rigacar"
    bl_label = "Анимация колес"
    bl_space_type = "VIEW_3D"
    bl_region_type = "UI"

    @classmethod
    def poll(cls, context):
        return PT_mixin.is_car_rig_generated(context)

    def draw(self, context):
        self.display_bake_section(context)


class PT_groundSensorsView(bpy.types.Panel, PT_mixin):
    bl_category = "Rigacar"
    bl_label = "Скелет автомобиля"
    bl_space_type = "VIEW_3D"
    bl_region_type = "UI"
    bl_options = {'DEFAULT_CLOSED'}

    @classmethod
    def poll(cls, context):
        return PT_mixin.is_car_rig_generated(context)

    def draw(self, context):
        self.display_ground_sensors_section(context)


def menu_entries(menu, context):
    menu.layout.operator(car_rig.OBJECT_OT_armatureCarDeformationRig.bl_idname, text="Скелет автомобиля", icon='AUTO')


classes = (
  PT_rigProperties,
  PT_groundSensorsProperties,
  PT_animationRigView,
  PT_wheelsAnimationView,
  PT_groundSensorsView,
)


def register():
    bpy.types.VIEW3D_MT_armature_add.append(menu_entries)
    for c in classes:
        bpy.utils.register_class(c)
    car_rig.register()
    bake_operators.register()


def unregister():
    bake_operators.unregister()
    car_rig.unregister()
    for c in classes:
        bpy.utils.unregister_class(c)
    bpy.types.VIEW3D_MT_armature_add.remove(menu_entries)


if __name__ == "__main__":
    register()
