
namespace gta {
	rage::gta_thread_vtable gta_thread_original{};
	rage::gta_thread_vtable gta_thread_new{};
	rage::gta_thread* gta_hooked_thread{};

	namespace native_addr {
		gta::functions::native_handler_t get_entity_speed_address{};
	}

	hooking::hooking() {
		using namespace native_addr;
		if (ptr_list->gta_thread_collection) {
			for (std::uint16_t i = 0; i < ptr_list->gta_thread_collection->count(); i++) {
				rage::gta_thread* thread = ptr_list->gta_thread_collection->at(i);

				if (thread) {

					if ((thread->get_context()->script_hash == 0x26fb4ab9 || thread->get_context()->script_hash == 1104607124 || thread->get_context()->script_hash == 3381724246) ||
						/*AltV*/(thread->get_context()->script_hash == 2003913879 || thread->get_context()->script_hash == 3522812357))
					{
						if (!gta_hooked_thread) {
							if (!gta_thread_original.deconstructor) {
								std::memcpy(&gta_thread_original, reinterpret_cast<std::uintptr_t*>(reinterpret_cast<std::uintptr_t*>(thread)[0]), sizeof(gta_thread_original));
								std::memcpy(&gta_thread_new, &gta_thread_original, sizeof(rage::gta_thread_vtable));
								gta_thread_new.run = hooks::script_thread;
							}

							if (reinterpret_cast<std::uintptr_t*>(thread)[0] != reinterpret_cast<std::uintptr_t>(&gta_thread_new)) {
								gta_hooked_thread = thread;
								reinterpret_cast<std::uintptr_t*>(thread)[0] = reinterpret_cast<std::uintptr_t>(&gta_thread_new);
							}
						}
					}
				}
			}
		}
		hooks_list = this;
	}

	hooking::~hooking() {
		if (gta_hooked_thread)
			reinterpret_cast<std::uintptr_t*>(gta_hooked_thread)[0] = reinterpret_cast<std::uintptr_t>(&gta_thread_original);

		using namespace native_addr; // remove natives funcs hooks
		//if (get_entity_speed_address) remove_hook(reinterpret_cast<void *>(get_entity_speed_address));

		hooks_list = nullptr;
	}

	rage::e_thread_state hooks::script_thread(rage::gta_thread* thread) {
		if (ptr_list->thread_switch_tls)
			ptr_list->thread_switch_tls(thread);



		//rage::native_queue->on_native_tick(); // для вызова нативов не из script_thread

		Beep(100, 100);
		call_native_functions();



		if (ptr_list->thread_call)
			return ptr_list->thread_call(thread);

		return gta_thread_original.run(thread);
	}

	//float hooks::get_entity_speed(rage::native_context& context) {
	//	//return reinterpret_cast<decltype(&get_entity_speed)>(originals::get_entity_speed)(context);
	//}
}