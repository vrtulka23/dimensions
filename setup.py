from setuptools import Extension, setup

setup(
    ext_modules=[
        Extension(
            name="dimensions",  # as it would be imported
                                # may include packages/namespaces separated by `.`
            sources=["src/dimensions.c","src/fraction.c"], # all sources are compiled into a single binary file
        ),
        Extension(
            name="fraction",  # as it would be imported
                                # may include packages/namespaces separated by `.`
            sources=["src/dimensions.c","src/fraction.c"], # all sources are compiled into a single binary file
        ),
    ]
)