#include "pybase.h"
#include <winrt/base.h>

PyObject* create_python_type(PyType_Spec* type_spec, PyObject* base_type)
{
    if (base_type != nullptr)
    {
        return PyType_FromSpecWithBases(type_spec, base_type);
    }
    else
    {
        return PyType_FromSpec(type_spec);
    }
}

py::pyobj_handle py::register_python_type(PyObject* module, const char* const type_name, PyType_Spec* type_spec, PyObject* base_type)
{
    py::pyobj_handle type_object{ create_python_type(type_spec, base_type) };
    if (!type_object)
    {
        throw winrt::hresult_error();
    }
    if (PyModule_AddObject(module, type_name, type_object.get()) != 0)
    {
        throw winrt::hresult_error();
    }
    return std::move(type_object);
}

void py::set_invalid_activation_error(const char* const type_name)
{
    std::string msg{ type_name };
    msg.append(" is not activatable");
    PyErr_SetString(PyExc_TypeError, msg.c_str());
}

PyTypeObject* py::winrt_type<py::winrt_base>::python_type;

PyDoc_STRVAR(winrt_base_doc, "base class for wrapped WinRT object instances.");

static PyObject* winrt_base_new(PyTypeObject* /* unused */, PyObject* /* unused */, PyObject* /* unused */)
{
    PyErr_SetString(PyExc_TypeError, "winrt_base is not directly constructable");
    return nullptr;
}

static void winrt_base_dealloc(py::winrt_wrapper<winrt::Windows::Foundation::IInspectable>* self)
{
    // auto hash_value = std::hash<winrt::Windows::Foundation::IInspectable>{}(self->obj);
    // py::wrapped_instance(hash_value, nullptr);
    self->obj = nullptr;
}

static PyType_Slot winrt_base_type_slots[] =
{
    { Py_tp_new, winrt_base_new },
    { Py_tp_dealloc, winrt_base_dealloc },
    { Py_tp_doc, winrt_base_doc},
    { 0, nullptr },
};

static PyType_Spec winrt_base_type_spec =
{
    "_%._winrt_base",
    sizeof(py::winrt_wrapper<winrt::Windows::Foundation::IInspectable>),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    winrt_base_type_slots
};

std::unordered_map<std::size_t, PyObject*> instance_map{};

void py::wrapped_instance(std::size_t key, PyObject* obj)
{
    // TODO: re-enable instance wrapper caching 

    // if obj is null, remove from instance_map
    //if (obj)
    //{
    //    auto insert = instance_map.try_emplace(key, obj);

    //    if (insert.second == false)
    //    {
    //        throw winrt::hresult_invalid_argument(L"wrapped WinRT object already cached");
    //    }
    //}
    //else
    //{
    //    // TODO: clean up the wrapped WinRT object. Currently leaking
    //    instance_map.extract(key);
    //}
}

PyObject* py::wrapped_instance(std::size_t key)
{
    //auto const it = instance_map.find(key);
    //if (it == instance_map.end())
    {
        return nullptr;
    }

    //return it->second;
}

static PyObject* init_apartment(PyObject* /*unused*/, PyObject* /*unused*/)
{
    winrt::init_apartment();
    Py_RETURN_NONE;
}

static PyObject* uninit_apartment(PyObject* /*unused*/, PyObject* /*unused*/)
{
    winrt::uninit_apartment();
    Py_RETURN_NONE;
}

static PyMethodDef module_methods[]{
    { "init_apartment", init_apartment, METH_NOARGS, "initialize the apartment" },
    { "uninit_apartment", uninit_apartment, METH_NOARGS, "uninitialize the apartment" },
    { nullptr }
};

static int module_exec(PyObject* module)
{
    winrt::handle_type<py::pyobj_ptr_traits> type_object { PyType_FromSpec(&winrt_base_type_spec) };
    if (!type_object)
    {
        return -1;
    }
    if (PyModule_AddObject(module, "_winrt_base", type_object.get()) != 0)
    {
        return -1;
    }
    py::winrt_type<py::winrt_base>::python_type = reinterpret_cast<PyTypeObject*>(type_object.detach());

    return 0;
}

static PyModuleDef_Slot module_slots[] = {
    {Py_mod_exec, module_exec},
    {0, nullptr}
};

PyDoc_STRVAR(module_doc, "_%");

static PyModuleDef module_def = {
    PyModuleDef_HEAD_INIT,
    "_%",
    module_doc,
    0,
    module_methods,
    module_slots,
    nullptr,
    nullptr,
    nullptr
};

PyMODINIT_FUNC
PyInit__%(void)
{
    return PyModuleDef_Init(&module_def);
}