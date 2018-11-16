
namespace xlang::impl
{
    template <typename T, typename Container>
    struct observable_vector final :
        implements<observable_vector<T, Container>, IObservableVector<T>, IVector<T>, IVectorView<T>, IIterable<T>>,
        observable_vector_base<observable_vector<T, Container>, T>
    {
        static_assert(std::is_same_v<Container, std::remove_reference_t<Container>>, "Must be constructed with rvalue.");

        explicit observable_vector(Container&& values) : m_values(std::forward<Container>(values))
        {
        }

        auto& get_container() noexcept
        {
            return m_values;
        }

        auto& get_container() const noexcept
        {
            return m_values;
        }

    private:

        Container m_values;
    };
}

WINRT_EXPORT namespace xlang
{
    template <typename T, typename Allocator = std::allocator<T>>
    IVector<T> single_threaded_vector(std::vector<T, Allocator>&& values = {})
    {
        return make<impl::input_vector<T, std::vector<T, Allocator>>>(std::move(values));
    }

    template <typename T, typename Allocator = std::allocator<T>>
    IObservableVector<T> single_threaded_observable_vector(std::vector<T, Allocator>&& values = {})
    {
        return make<impl::observable_vector<T, std::vector<T, Allocator>>>(std::move(values));
    }
}
